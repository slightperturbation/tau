/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.

#include "OdeRobot.hpp"

using namespace tau;


/////////////////////////////////////////////////
// OdeJoint

OdeJoint::OdeJoint( OdeRobot* robot, dJointID aJointID )
: m_robot( robot ),
  m_jointID( aJointID ),
  m_treeXForm( XForm::identity() ),
  m_S( MatrixNxN::Zero(6,6) )
{
    // Noop
}

Body*
OdeJoint::body()
{
    dBodyID parent = dJointGetBody( m_jointID, 0 ); // 0 is the proximal body
    return m_robot->getBodyFromOdeID( parent );
}

const Body* 
OdeJoint::body() const  
{ 
    dBodyID parent = dJointGetBody( m_jointID, 0 ); // 0 is the proximal body
    return m_robot->getBodyFromOdeID( parent );
}

dBodyID 
OdeJoint::odeProximalBody()
{
    return dJointGetBody( m_jointID, 0 );
}

dBodyID
OdeJoint::odeDistalBody()
{
    return dJointGetBody( m_jointID, 1 );
}

Matrix3x3
OdeJoint::distalBody_from_world()
{
    Matrix3x3 rot;
    dBodyID body = odeDistalBody();
    const dReal* odeRot = dBodyGetRotation( body );
    rot << odeRot[0], odeRot[1], odeRot[2],
           odeRot[4], odeRot[5], odeRot[6],
           odeRot[8], odeRot[9], odeRot[10];
    return rot;
}

Matrix3x3
OdeJoint::proximalBody_from_world()
{
    Matrix3x3 rot;
    dBodyID body = odeProximalBody();
    const dReal* odeRot = dBodyGetRotation( body );
    rot << odeRot[0], odeRot[1], odeRot[2],
           odeRot[4], odeRot[5], odeRot[6],
           odeRot[8], odeRot[9], odeRot[10];
    return rot;
}

Vector3
OdeJoint::proximalJointAnchor_in_world()
{
    Vector3 out = Vector3::Zero();
    // get the proximal body, assume 0 body is proximal
    dBodyID proxBody = dJointGetBody( m_jointID, 0 );
    if( !proxBody )
    {
        return out;
    }
    dJointID proxJoint = 0;
    int numProxJoints = dBodyGetNumJoints( proxBody );
    for( int i=0; i<numProxJoints; ++i )
    {
        dJointID jId = dBodyGetJoint( proxBody, i );
        // find joint where proxBody is distal (to that joint)
        // this is the proximal (upstream) joint from this.
        if( proxBody == dJointGetBody( jId, 1 ) )
        {
            // found it
            proxJoint = jId;
            break;
        }
    }
    if( !proxJoint )
    {
        errorLog() << "CAUTION proximalJointAnchor_in_world: no proximal joint for joint.  "
                << "Maybe calling on the 0th joint?  Returning the proximal BODY's COM, "
                << "instead of the proximal joint's anchor!\n";
        Vector3 out;
        const dReal* com = dBodyGetPosition( proxBody );
        for( int i=0;i<3;++i ) out[i] = com[i];
        return out;
    }
    else
    {
        return getJointAnchorInWorld( proxJoint );
    }
}

Vector3
OdeJoint::jointAnchor_in_world()
{
    return getJointAnchorInWorld( m_jointID );
}

void
OdeJoint::associateDistalBody( OdeBody* distalBody )
{
    distalBody->setJoint( this );
}

/////////////////////////////////////////////////
// OdeRevoluteJoint

OdeRevoluteJoint::OdeRevoluteJoint( OdeRobot *robot, dJointID jointID )
: OdeJoint( robot, jointID ),
  m_override( false ),
  m_override_q( 0 ),
  m_override_dq( 0 ),
  m_ddq( 0 )
{
    assert( dJointGetType( m_jointID ) == dJointTypeHinge );

    Vector3 r = jointAnchor_in_world() - proximalJointAnchor_in_world();
    // note using transpose for inverse since the 3x3 is a rotation.

    // E converts from distal frame to proximal frame
    Matrix3x3 E = proximalBody_from_world() * distalBody_from_world().transpose();
    // E converts from proximal frame to distal frame
    //Matrix3x3 E = distalBody_from_world() * proximalBody_from_world().transpose();

    m_treeXForm = XForm( E, r );
    std::cerr << "Creating ODE RevoluteJoint with anchorFrame:\n" << m_treeXForm << "\n\n";

    dVector3 axis;
    dJointGetHingeAxis( jointID, axis );

    m_S = MatrixNxN::Zero( 6, 1 );

    for( int i=0; i<3; ++i ) m_S[i] = axis[i];

    // TODO - $$$$$
    //  COMPLETE HACK -- there's something wrong with the
    //  represnetation of the axis between ODE and TAU here.
    //  this hack flips the sign for y-axis hinges only.
    //  Seems clear this is a handedness confusion-- but where's the
    //  assumption of handedness in either system?
    //  It's got to be in the application/computation of torque.
    //  Maybe tau's computation of the spatial torque is using
    //  the wrong spatial cross product operator (force vs. motion)
    //  somewhere??

//    if( std::abs(m_S[1]) > 0.5 )
//    {
//        m_S[1] *= -1;
//        m_S[2] *= -1;
//    }

    //  END HACK

//    m_S[2] = 1;

//    for( int i = 0; i<3; ++i )
//    {
//        dVector3 basis;
//        for( int j=0; j<3; ++j ) basis[j] = i == j ? 1 : 0;
//        double dot = dDOT( basis, axis );
//        if( dot > 0 )
//        {
//            m_S[i] = 1;
//        }
//    }
    errorLog() << "motion subspace computed as: \n" << m_S << "\n";
    //assert( m_S[0] + m_S[1] + m_S[2] > 0.9 );

}

XForm
OdeRevoluteJoint::xform() const
{
    Vector3 axis;
    for( size_t i=0; i<3; ++i )
    {
        axis[i] = m_S[i];
    }

    Matrix3x3 rotMatrix = rotFromAxisAngle( axis, q(0) );
    XForm out = XForm::fromRotationMatrix( rotMatrix );

//    XForm out;
//    Matrix3x3 rX = rotX( q(0) );
//    Matrix3x3 rY = rotY( q(0) );
//    Matrix3x3 rZ = rotZ( q(0) );

//    if( axis[0] > 0.1 )
//    {
//        out = XForm::fromRotationMatrix( rX );
//    }
//    else if( axis[1] > 0.1 )
//    {
//        out = XForm::fromRotationMatrix( rY );
//    }
//    else if( axis[2] > 0.1 )
//    {
//        out = XForm::fromRotationMatrix( rZ );
//    }
//    else
//    {
//        errorLog() << "Error in axis -- only support axis-aligned.";
//    }
    return out;
}


MatrixNxN
OdeRevoluteJoint::constraintSubspace( void )
{
    errorLog() << "Error constraintSubspace not finished!";
    MatrixNxN T( 3, 2 ); // row, col
    T.setZero();
    if( m_S[0] )
    {
        T(1,0) = 1; T(2,1) = 1;
    }
    else if( m_S[1] )
    {
        T(0,0) = 1; T(2,1) = 1;
    }
    else if( m_S[2] )
    {
        T(0,0) = 1; T(1,1) = 1;
    }
    MatrixNxN outT( 6, 5 );
    outT.setZero();
    for( int r=0; r<3; r++ ) for( int c=0; c<2; c++ )
    {
        outT(r,c) = T(r,c);
    }
    for( int r=3; r<6; ++r )
    {
        outT(r,r-1) = 1;
    }
//     //TODO:  HARDCODED TO +Z AXIS!  IGNORES ODE'S AXIS
//    // http://www.sciforums.com/showthread.php?t=77769 for computing subspaces
//    // (formulate as a linear problem)
    MatrixNxN out( 6, 5 );
    out.setZero();
    out(0,0) = 1;
    out(1,1) = 1;
    out(3,2) = 1;
    out(4,3) = 1;
    out(5,4) = 1;
    if( m_S[2] > 0.9 )
    {
        errorLog() << "*** computed z-axis constraint subspace using old method: \n" << out << "\n";
    }

    errorLog() << "*** computed constraint subspace using new method: \n" << outT << "\n";

    return outT;
}

double
OdeRevoluteJoint::q( int index ) const
{
    assert( index == 0 );
    if( m_override )
    {
        return m_override_q;
    }
    //ODE gives the relative rotation with respect to the Hinge axis of Body 1 with respect to Body 2
    return - dJointGetHingeAngle( m_jointID );
}

double
OdeRevoluteJoint::dq( int index ) const
{
    assert( index == 0 );
    if( m_override )
    {
        return m_override_dq;
    }
    // ODE gives Body1 WRT body2, so invert it
    return - dJointGetHingeAngleRate( m_jointID );
}


/////////////////////////////////////////////////
// OdeBody

OdeBody::OdeBody( OdeRobot* robot, dBodyID odeBodyID )
: m_robot( robot ),
  m_bodyID( odeBodyID ),
  m_joint( NULL )
{
    m_robot->addBody( this );

    // In ctor, we need to build the body, add it to the robot, and set the inertia
    // first, ensure that this body doesn't already exist in the robot
    assert( m_robot->m_bodyMap.end() == m_robot->m_bodyMap.find( m_bodyID ) );
    // add us to the OdeRobot's mapping for ode ID's
    m_robot->m_bodyMap[m_bodyID] = this;

    // Find the joint that is the parent of this body.  Assert that there is at most one.
    int numJoints = dBodyGetNumJoints( m_bodyID );
    int numProximalJoints = 0; // where proximal joints have this body as body 0
    dJointID proximalJointID = 0;
    for( int i = 0; i < numJoints; i++ )
    {
        dJointID jointID = dBodyGetJoint( m_bodyID, i );
        if( m_bodyID == dJointGetBody( jointID, 1 ) )
        {
            numProximalJoints++;
            proximalJointID = jointID;
        }
    }
    assert( numProximalJoints <= 1 );  // there should be only one joint proximal to this body (no kinematic loops)

    Matrix3x3 comRotation_local = Matrix3x3::Identity();
    Vector3 comPosition_local = Vector3::Zero();

    if( numProximalJoints == 0 )
    {
        // this is the root body
        // for the root body, the frame is actually at the COM
        // this discrpency doesn't hurt, since the root is 
        // considered fixed
    }
    else
    {
        // this is not the root body, i.e., the general case
        // here we use the position of the frame of the preceeding joint
        // to define the frame of this body
        // note that the COM must be displaced by an equal amount (in opposite direction)
        assert( proximalJointID );

        m_parent = m_robot->getBodyFromOdeID( dJointGetBody( proximalJointID, 0 ) ); // get proximal
        
        Vector3 anchor_world = getJointAnchorInWorld( proximalJointID );
        const dReal* com_world = dBodyGetPosition( m_bodyID ); // actual COM in world
        Vector3 bodyCoM_world( com_world[0], com_world[1], com_world[2] );
        
        // so the COM relative to the anchor (which is the world of the new body frame for tau)
        comPosition_local = bodyCoM_world - anchor_world; // used in SpatialInertia
        
        // now, body's frame in world coords is anchor_W
        // and the frame's orientation is unchanged, so 
        // the spatial mass can be updated by moving it by c.

        dMass mass;
        dBodyGetMass( m_bodyID, &mass );

        for( int i=0; i<3; ++i ) comPosition_local[i] = mass.c[i] + comPosition_local[i];

        Vector6 I;
        int i = 0;
        for( int r=0; r<3; ++r )
        {
            for( int c=0; c<=r; ++c )
            {
                // mass.I in row-major order
                I(i++) = mass.I[4*r + c];
            }
        }

        //TODO:  to allow variable axis of rotation, the spatial inertia needs to allow a rotation.

        errorLog() << "Creating tau::OdeBody " << m_robot->bodyIndex(this) << " with Inertia at "
                << "com=" << comPosition_local << ", mass=" << mass.mass << " and I=\n" << I << "\n";
        
        m_inertia = SpatialInertia( mass.mass, comPosition_local, I );
    }
}

OdeBody::~OdeBody()
{
    // Remove me from my robot's list
    m_robot->m_bodyMap.erase( m_bodyID );
}

void
OdeBody::setOdeState()
{
    // assuming the zeroth body is the root

    Matrix3x3 invE = xForm_body_from_base().E().transpose();
    Vector3 h = invE * inertia().h();
    Vector3 r = xForm_body_from_base().r() + h ;
    errorLog() << "Body from base, translation: " << r << "\n";

    dBodySetPosition( m_bodyID, r[0], r[1], r[2] );
    errorLog() << "Setting dBodyID=" << getOdeBodyID() << " r = " << r << "\n";

    //const Matrix3x3& E = comXForm.E(); //xForm_body_from_base().E();
    dMatrix3 R;
    for( int i=0; i<3; ++i ) for( int j=0; j<3; ++j )
    {
        R[i*4+j] = invE(i,j);
    }
    dBodySetRotation( m_bodyID, R );
    errorLog() << "Setting dBodyID=" << getOdeBodyID() << " invE = \n" << invE << "\n";

}


/////////////////////////////////////////////////
// OdeRobot

OdeRobot::OdeRobot( dBodyID rootBody )
{
    errorLog() << "\n-----------\nDEBUG: CREATING ROBOT:\n" << dumpOdeTree( rootBody ) << "\n-----------\n";

    // note that the second argument is NULL, indicating that the root body
    // doesn't have an associated joint.
    addOdeBodyRecursive( rootBody, NULL );
}

void
OdeRobot::applyComputedTorque()
{
    //errorLog() << "-----------applyComputedTorque()--------------\n";
    //errorLog() << "\t BodyCount=" << bodyCount() << "\n";
    for( size_t i=1; i<bodyCount(); ++i )
    {
        Body* b = body( i );
        if( b && !(b->isBase()) )
        {
            //errorLog() << "\tHave body " << i << "\n";
            Joint* j = b->joint();
            if( j )
            {
                //errorLog() << "\thave joint id = " << i
                //        << ", \ttorque = "
                //        << j->getComputedTorque() << "\n";
                j->applyComputedTorque();
            }
        }
    }
}

void
OdeRobot::addOdeBodyRecursive( dBodyID bodyID, OdeJoint* proximalJoint )
{
    // create a body and add it to this robot
    // this creation is responsible for correctly setting the body's COM
    // and inertia matrix.
    // If this body is the root, it's Frame is it's own COM,
    // if it is not the root, it's Frame is it's proximal joint's anchor.
    // note that the OdeBody ctor adds itself to the robot, so we can
    // ignore the returned pointer.
    OdeBody* newBody = new OdeBody( this, bodyID );
    proximalJoint->associateDistalBody( newBody );

    int numJoints = dBodyGetNumJoints( bodyID );
    for( int i = 0; i < numJoints; i++ )
    {
        OdeJoint* distalJoint = NULL;
        // only want to add joints where this body is the parent (proximal)
        dJointID jointID = dBodyGetJoint( bodyID, i );
        if( bodyID == dJointGetBody( jointID, 0 ) )
        {
            //errorLog() << "In addOdeBodyRecursive, adding joint: " << jointID << "\n";
            // newOdeJoint determines which subclass should be built,
            // and is responsible for adding the joint to this robot.
            distalJoint = addOdeJoint( jointID );
            if( distalJoint )
            {
                addOdeBodyRecursive( distalJoint->odeDistalBody(), distalJoint );
            }
            else
            {
                errorLog() << "Failed to add ODE JointID = " << jointID << "\n";
            }
        }
    }
}

OdeBody*
OdeRobot::getBodyFromOdeID( dBodyID argBody )
{
    return m_bodyMap[ argBody ];
}

OdeJoint*
OdeRobot::getJointFromOdeID( dJointID argJoint )
{
    const int CHILD = 1;
    dBodyID bodyID = dJointGetBody( argJoint, CHILD );
    OdeBody* body = getBodyFromOdeID( bodyID );
    return dynamic_cast<OdeJoint*>( body->joint() );
}

OdeJoint* 
OdeRobot::addOdeJoint( dJointID odeJointID )
{
    OdeJoint* newJoint = 0;
    switch( dJointGetType( odeJointID ) )
    {
        case dJointTypeHinge:
            newJoint = new OdeRevoluteJoint( this, odeJointID );
            break;
        default:
            errorLog() << "Error:  Unknown joint type(" << dJointGetType( odeJointID )
            << ") for joint " << reinterpret_cast<long int>( odeJointID ) << "\n";
    }
    return newJoint;
}

OdeJoint*
OdeRobot::odeJoint( unsigned int index )
{
    return dynamic_cast< OdeJoint* >( joint(index) );
}

const OdeJoint*
OdeRobot::odeJoint( unsigned int index ) const
{
    return dynamic_cast< const OdeJoint* >( joint(index) );
}

OdeBody*
OdeRobot::odeBody( unsigned int index )
{
    return dynamic_cast< OdeBody* >( body( index ) );
}

const OdeBody*
OdeRobot::odeBody( unsigned int index ) const
{
    return dynamic_cast< const OdeBody* >( body( index ) );
}


void
OdeRobot::setOdeState()
{
    for( size_t i=1; i<bodyCount(); ++i )
    {
        OdeBody* b = odeBody( i );
        if( b )
        {
            b->setOdeState();
        }
    }
}


/////////////////////////////////////////////////
/// Free Functions 

Vector3 tau::getJointAnchorInWorld( dJointID joint )
{
    Vector3 a;
    dVector3 tmp;
    switch( dJointGetType( joint ) )
    {
        case dJointTypeHinge:
            dJointGetHingeAnchor( joint, tmp );
            break;
    case dJointTypeUniversal:
            dJointGetUniversalAnchor( joint, tmp );
            break;
    case dJointTypeBall:
            dJointGetBallAnchor( joint, tmp );
            break;
    }
    a << tmp[0], tmp[1], tmp[2];
    return a;
}

std::string tau::dumpOdeTree( dBodyID root, int depth )
{
    if( depth > 5 )
    {
        return "MAX RECURSION DEPTH REACHED\n";
    }
    std::string indent;
    for( int i=0; i<depth; ++i ) indent += "\t";

    std::ostringstream out;
    out << indent << "BodyID=" << root ;
    if( root )
    {
        const dReal* com = dBodyGetPosition( root );
        out << " COM=[" << com[0] << ", " << com[1] << ", " << com[2] << "]";
    }
    else
    {
        return out.str();
    }
    out << "\n";
    indent += "--> ";
    for( int j=0; j<dBodyGetNumJoints( root ); ++j )
    {
        dJointID joint = dBodyGetJoint( root, j );
        out << indent << "Joint " << j << ", ID=" << joint << ", ";
        if( joint )
        {
            dJointType type = dJointGetType( joint );
            switch( type )
            {
            case dJointTypeHinge:
                out << "[Hinge] ";
                break;
            case dJointTypeFixed:
                out << "[Fixed] ";
                break;
            default:
                out << "[OTHER] ";
            }
            out << "BodyIDs=(" << dJointGetBody( joint, 0 ) << ", " << dJointGetBody( joint, 1 ) << ")";
        }
        out << "\n";
        if( dJointGetBody(joint, 0) == root )
        {
            // outbound body
            dBodyID distalBody = dJointGetBody(joint, 1);
            if( distalBody )
            {
                if( distalBody != root )
                {
                    out << dumpOdeTree( dJointGetBody(joint, 1), depth+1 );
                }
                else
                {
                    out << indent << "\t***** WARNING: Distal body same as parent for joint.\n";
                }
            }
        }
    }
    return out.str();
}
