/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.

#include "robot.hpp"

using namespace tau;

/// should be inline, but need to break out for debugging
void
tau::Body
::setXForm_body_from_base( const XForm& arg )
{
    cached_body_from_base = arg;
}

Body*
tau::Robot
::root()
{
    if( bodies.empty() )
    {
        return NULL;
    }
    return bodies[ 0 ];
}

Body*
tau::Robot
::body( unsigned int index )
{
    if( index >= bodies.size() )
    {
        return NULL;
    }
     return bodies[ index ];
}

const Body*
tau::Robot
::body( unsigned int index ) const
{
    if( index >= bodies.size() )
    {
        return NULL;
    }
    return bodies[ index ];
}

int
tau::Robot
::bodyIndex( const Body* arg ) const
{
    for( size_t i=0; i<bodies.size(); ++i )
    {
        if( bodies[i] == arg )
        {
            return i;
        }
    }
    errorLog() << "No such body ("
    << reinterpret_cast<long int>(arg) << ") found in this robot ("
    << reinterpret_cast<long int>(this) << ")";
    return -1;
}

Joint*
tau::Robot
::joint( unsigned int index )
{
     Body* b = body( index );
    if( !b )
    {
        return NULL;
    }
    return b->joint();
}

const Joint*
tau::Robot
::joint( unsigned int index ) const
{
    const Body* b = body( index );
    if( !b )
    {
        return NULL;
    }
    return b->joint();
}

Body*
tau::Robot
::parent( unsigned int index )
{
    if( index >= bodies.size() )
    {
        return NULL;
    }
    return bodies[ index ]->parent();
}


void
tau::Robot
::solveKinematics( int debugLevel )
{
    for( size_t i = 1; i < bodies.size(); ++i )
    {
        if( debugLevel > 0 ) errorLog() << "------\n-----Kinematics for Body " << i << " -------\n";

        Body* b = bodies[i];
        // since b is not the root, it has both a joint and a parent
        assert( b->parent() );
        assert( b->joint() );
        Joint* j = b->joint();  // joint connecting i to the parent body, \lambda(i) 
        assert( j );
        if( debugLevel > 0 ) errorLog() << "joint lambda(i), treeXform:\n" << j->treeXForm() << "\n";
        if( debugLevel > 0 ) errorLog() << "joint lambda(i), xform(q="
                << j->q()
                << "):\n" << j->xform() << "\n";

        XForm body_from_parent = j->xform() * j->treeXForm();

//        if( debugLevel > 0 ) errorLog() << "xform, body_from_parent:\n" << body_from_parent << "\n";

        // Recursively compute the base-to-body transform
        if( b->parent()->isBase() )
        {
            if( debugLevel > 0 ) errorLog() << "body parent is base\n";
            if( debugLevel > 0 ) errorLog() << "\txform, body_from_parent:\n" << body_from_parent << "\n----\n";

            b->setXForm_body_from_base( body_from_parent );
        }
        else
        {
            if( debugLevel > 0 ) errorLog() << "body parent is NOT base\n";

            XForm parent_from_base = b->parent()->xForm_body_from_base();
            XForm body_i_from_base = body_from_parent * parent_from_base;
//            XForm body_i_from_base = parent_from_base * body_from_parent;

            b->setXForm_body_from_base( body_i_from_base );

            if( debugLevel > 0 ) errorLog() << "\txform, parent_from_base:\n" << parent_from_base << "\n----\n";
            if( debugLevel > 0 ) errorLog() << "\txform, body_from_parent:\n" << body_from_parent << "\n----\n";
            if( debugLevel > 0 ) errorLog() << "\txform, body_i from base:\n" << body_i_from_base << "\n----\n";
        }
//        if( debugLevel > 0 ) errorLog() << "{}^{F_i}X_{F_0} = \n"
//                << b->xForm_body_from_base()  << "\n\n";

//        SMV z;
//        z[5] = 1.0;
//        if( debugLevel > 0 ) errorLog() << " applying body_from_base to unit-z vector (translation) : "
//                                        << ( b->xForm_body_from_base().apply( z ) ).second()
//                                        << "\n";

        
        // depends on q, dq and ddq being set already
        if( debugLevel > 1 ) errorLog() << "q=" << j->q()
            << ", dq=" << j->dq()
            << ", ddq=" << j->ddq()
            << "\n";
        SMV v_J = j->v_J();
        if( debugLevel > 1 ) errorLog() << "v_J=" << v_J << "\n";

        SMV c_J = j->c_J();
        if( debugLevel > 1 ) errorLog() << "c_J=" << c_J << "\n";

        MatrixNxN S = j->motionSubspace();
        if( debugLevel > 1 ) errorLog() << "S=" << S << "\n";

        VectorN ddq = j->ddq();
        
        SMV v_i = body_from_parent.apply( b->parent()->v() ) + v_J;
        if( debugLevel > 1 ) errorLog() << "v_i=" << v_i << "\n";
        SMV a_i = body_from_parent.apply( b->parent()->a() )
                      + SMV(S * ddq)
                      + c_J
                      + SMV(v_i.skewSym() * v_J.asVector6())
                      ;
        if( debugLevel > 1 ) errorLog() << "a_i=" << a_i << "\n";

        SFV ext_f = b->externalForce();

        if( debugLevel > 2 ) errorLog() << "v_i=\n" << v_i << "\n";
        Matrix6x6 vSkewSymAsForce = SFV(v_i.asVector6()).skewSym();
        if( debugLevel > 2 ) errorLog() << "vSkewSymAsForce=\n" << vSkewSymAsForce << "\n";

        const SpatialInertia& inertia = b->inertia();

        if( debugLevel > 3 ) errorLog() << "inertia=\n" << inertia << "\n"
                << "spatial matrix: \n" << inertia.inertiaMatrix() << "\n";

        SFV f_i = SFV( (inertia * a_i).asVector6()
                      + ( vSkewSymAsForce * ( inertia * v_i ).asVector6() )
                      - (b->xForm_body_from_base().apply( ext_f )).asVector6() );

        if( debugLevel > 1 ) errorLog() << "f_i=" << f_i << "\n";

        // here we have v_i, a_i and f_i representing the full description of body i,
        // store it in the body in preparation for the next loop (in solveInverseDynamics),
        // where these are used to compute the torques.
        b->setSpatialVelocity( v_i );
        b->setSpatialAcceleration( a_i );
        b->setSpatialForce( f_i );
    }
}

void 
tau::Robot
::solveInverseDynamics( int debugLevel )
{
    solveKinematics( debugLevel );
    
    for( int i = bodies.size() - 1; i > 0; --i )
    {
        // compute:
        // \tau_i = S_i^T f_i

        if( debugLevel > 0 ) errorLog() << "------\n-----InvDyn for Body " << i << " -------\n";
        Body* b = bodies[i];
        Joint* j = b->joint();
        MatrixNxN S_i = j->motionSubspace();

        if( debugLevel > 0 ) errorLog() << "\tmotion subspace: \n" << S_i << "\n";

        SFV f_i = b->spatialForce();

        if( debugLevel > 0 ) errorLog() << "\tbody's spatialForce: \n" << f_i << "\n";

        VectorN tau_i = S_i.transpose() * f_i.asVector6();  // vector size is number of DOFs

        if( debugLevel > 0 ) errorLog() << "\ttau_i (size should be # of dofs): \n" << tau_i << "\n";

        j->setComputedTorque( tau_i );

        if( ! b->parent()->isBase() )
        {
            // update the force on the parent
            //
            // f_{\lambda(i)} = f_{\lambda(i)} + {}^{\lambda(i)}X_i^* f_i
            //
            XForm body_from_parent = j->xform() * j->treeXForm();
            XForm parent_from_body = body_from_parent.inverse();
            SFV f_i_inParentFrame = parent_from_body.apply( f_i ); // could use invapply for eff.

//            SFV f_p = b->parent()->spatialForce();

            if( debugLevel > 0 ) errorLog() << "\tf_i_inParentFrame:\n" << f_i_inParentFrame << "\n";

//            SFV f_p_new = SFV( f_p.asVector6() + body_from_parent.invApply( f_i ).asVector6() );
            SFV f_p_new = b->parent()->spatialForce() + body_from_parent.invApply( f_i );

            b->parent()->setSpatialForce( f_p_new );
        }
    }
}
