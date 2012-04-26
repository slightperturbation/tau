/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.


#include "TauRobot.hpp"

using namespace tau;

tau::TauJoint
::TauJoint( Body* aParent, 
            Body* aChild, 
            XForm aTreeXForm, 
            MatrixNxN aMotionSubspace )
:   parent_( aParent ), 
    child_( aChild ),
    m_treeXForm( aTreeXForm ), 
    S_( aMotionSubspace )
{
    assert( parent_ );
    assert( child_ );
    child_->setJoint( this );
    // only try to set the parent of a TauBody
    TauBody* aTauChild = dynamic_cast< TauBody* >( aChild );
    if( aTauChild )
    {
        aTauChild->setParent( parent_ );
    }
}

tau::TauRevoluteJoint
::TauRevoluteJoint( Body* aParent, 
                    Body* aChild, 
                    Vector3 aAnchorPoint, 
                    Vector3 aAxis )
: TauJoint( aParent, aChild ),
  m_q( 0 )
{
    // aAnchorPoint and aAxis define the xform (in frame zero) for this joint:
    Matrix3x3 E = rotFromTwoVectors( aAxis, Vector3( 0,0,1 ) );
    m_treeXForm = XForm( E, aAnchorPoint );
    std::cerr << "Creating RevoluteJoint with anchorFrame:\n" << m_treeXForm << "\n\n";
    
    // assume the joint axis is aligned to +Z
    S_.setZero();
    S_(2) = 1;
}


/// CAUTION!  not complete
void
tau::TauRevoluteJoint
::setAnchorAndAxisInFrame0( Vector3 aAnchorPoint, Vector3 aAxis )
{
    assert( false );
    
    // aAnchorPoint and aAxis define the xform (in frame zero) for this joint:
    Matrix3x3 E = rotFromTwoVectors( aAxis, Vector3( 0,0,1 ) );
    XForm X_Fi_from_F0( E, aAnchorPoint );
    
    // aAnchorPoint and aAxis are in world (frame zero) coordinates
    // so need to convert to parent body's frame.
    XForm X_F0_from_Fp = body()->xForm_body_from_base().inverse();
    
    //Todo: Rotate anchor so that aAxis is aligned with the Z-axis.
    //Todo: r determined from anchorPoint
    m_treeXForm = X_Fi_from_F0 * X_F0_from_Fp; // anchor == X_Fi_from_Fp
    
    // assume the joint axis is aligned to +Z
    S_.setZero();
    S_(2) = 1;
}

void
tau::TauRevoluteJoint
::q( int index, Scalar state )
{
    assert( index == 0 );
    m_q = state;
}

double 
tau::TauRevoluteJoint
::q( int index ) const 
{
    assert( index == 0 );
    return m_q;
}

VectorN
tau::TauRevoluteJoint
::q() const
{
    VectorN out(stateSize(),1);
    out(0,0) = m_q;
    return out;
}

void
tau::TauRevoluteJoint
::dq( int index, Scalar dstate )
{
    assert( index == 0 );
    m_dq = dstate;
}

double 
tau::TauRevoluteJoint
::dq( int index ) const
{
    assert( index == 0 );
    return m_dq;
}

VectorN
tau::TauRevoluteJoint
::dq() const
{
    VectorN out(stateSize(),1);
    out(0,0) = m_dq;
    return out;
}

void 
tau::TauRevoluteJoint
::ddq( int index, Scalar ddstate )
{
    assert( index == 0 );
    m_ddq = ddstate;
}

double 
tau::TauRevoluteJoint
::ddq( int index ) const
{
    assert( index == 0 );
    return m_ddq;    
}

VectorN
tau::TauRevoluteJoint
::ddq() const
{
    VectorN out(stateSize(),1);
    out(0,0) = m_ddq;
    return out;
}



