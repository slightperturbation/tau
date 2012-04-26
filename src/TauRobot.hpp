/// 
/// \file TauRobot.hpp
/// \brief Concrete classes that represent rigid-bodies and their 
/// constraints (joints).  Each class holds own data (as opposed to wrapping
/// some other data)
/// Note that, despite the file name, there is no TauRobot-- the   Robot class
/// uses concrete joints and bodies through their interfaces, so a "TauRobot"
/// is really just a   Robot composed of   TauJoint and   TauBody instances.
///
/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.
///

#ifndef TAU_TAUROBOT_HPP_
#define TAU_TAUROBOT_HPP_

#include "robot.hpp"

namespace tau
{
    class TauBody;
    
	/// Joint is the abstract super-class for scleronomic joints (ie, joints
	/// not dependent on time (rheonomic) nor on the derivatives of the 
	/// generalized coordinates (nonholonomic)).
	class TauJoint : public Joint
	{
	public:
        TauJoint( Body* aParent, 
                  Body* aChild, 
                  XForm aTreeXForm = XForm::identity(), 
                  MatrixNxN aMotionSubspace = MatrixNxN::Identity( 6, 1 ) );
        virtual ~TauJoint() {}
        
		virtual MatrixNxN motionSubspace( void ) = 0;
        virtual MatrixNxN constraintSubspace( void ) = 0;
            
        virtual Body* body() { return child_; }
        virtual const Body* body() const  { return child_; }
        
        virtual const XForm& treeXForm() const 
        {
            // returns the transform from the parent body to the "anchor"
            // of this joint.
            return m_treeXForm;
        }
        
        virtual XForm& treeXForm() 
        {
            return m_treeXForm;
        }
		
        /// Sets the parent body of this body to \a proximalBody.
        virtual void setParent( Body* proximalBody )
        {
            parent_ = proximalBody;
        }
		
    protected:        
        Body* parent_; //< Body proximal to the joint.
        Body* child_; //< Body this joint controls, ie, body just distal to joint.  (returned by body())
        XForm m_treeXForm; //< /f$ X_T(i) = {}^{\lambda(i),i}X_{\lambda(i)} /f$ The "tree" transform, from the parent body to the joint's anchor.
		MatrixNxN S_;
	};
	
	/// A concrete revolute joint.
	class TauRevoluteJoint : public TauJoint
	{
	public:		
		/// Both aAxis and aAnchor should be in world coordinates.
		/// The position relative to the parent is calculated when the
		/// joint is attached to its parent.
        /// The \a aAnchorPoint and \a aAxis are assumed to be in the associated \a Body's 
        /// frame, i.e., for   Joint i, they are assumed to be in frame of   Body i. 
        /// Note here the axis for the joint is internally assumed to be +z.  The "tree" XForm
        /// is reponsible for rotating the system so that desired axis becomes +z.
		/// See RGBA Table 4.1
		TauRevoluteJoint( Body* aParent, 
                          Body* aChild, 
                          Vector3 aAnchorPoint, 
                          Vector3 aAxis );
        
		virtual ~TauRevoluteJoint() {}
        
        /// CAUTION!  not complete
        void setAnchorAndAxisInFrame0( Vector3 aAnchorPointInFrame0, Vector3 aAxisInFrame0 );
        
		virtual MatrixNxN motionSubspace( void )
		{
			return S_;
		}
        
        virtual MatrixNxN constraintSubspace( void )
		{
            MatrixNxN out( 6, 5 );
            out.setZero();
            out(0,0) = 1;
            out(1,1) = 1;
            out(3,2) = 1;
            out(4,3) = 1;
            out(5,4) = 1;
            return out;
        }
         
        virtual SMV spatialVelocityAcrossJoint()
		{
			return SMV( motionSubspace() * m_dq );
		}
        
        virtual unsigned int stateSize() const
        {
            return 1;
        }
        
		virtual XForm xform() const
		{
			return XForm::fromRotationMatrix( rotZ( m_q ) );
		}
        
        virtual VectorN getComputedTorque() const
        {
            return cached_computed_torque;
        }
        
        /// The position of the joint.
        ///   stateSize()
        virtual void q( int index, Scalar state );
        virtual Scalar q( int index = 0 ) const ;
        virtual VectorN q() const;

        /// The rate of change of the joint.
        ///   stateSize()
        virtual void dq( int index, Scalar dstate );
        virtual Scalar dq( int index = 0 ) const;
        virtual VectorN dq() const;
        
        /// The 2nd derivative of the joint. Interpretted as the desired 
        /// rate of change of the joint for inverse dynamics.
        ///   stateSize()
        virtual void ddq( int index, Scalar ddstate );
        virtual Scalar ddq( int index = 0 ) const;     
        virtual VectorN ddq() const;

	protected:
        Scalar m_q;
        Scalar m_dq;
        Scalar m_ddq;
	};
	
	
    //	///
    //	class SphericalJoint : public Joint
    //	{
    //	public:
    //		SphericalJoint( Vector3 aAnchorPoint )
    //		{
    //		}
    //	};
	
    /// Concrete implementation of Body for testing.
	class TauBody : public Body
	{
	public:
        TauBody( Robot* aRobot, Body* aParent = 0, Joint* aJoint = 0 )
        : robot_( aRobot ),
          parent_( aParent ),
          joint_( aJoint )
        {
            if( !robot_ )
            {
                errorLog() << "ERROR: TauBody created with null robot.";
            }
            if( parent_ && robot_->bodyIndex( parent_ ) < 0 )
            {
                errorLog() << "ERROR: TauBody created for robot (" << reinterpret_cast<long int>(aRobot)
                << "), but the non-null parent body (" << reinterpret_cast<long int>(aParent)
                << ") doesn't belong to that robot.  I.e., must add parent body before child.";
            }
            // add this body to the robot
            robot_->addBody( this );
        }
        virtual ~TauBody() {}

        virtual void setInertia( const SpatialInertia& aInertia )
        {
            inertia_ = aInertia;
        }
        
        virtual SpatialInertia inertia() const
        {
            return inertia_;
        }
        
        virtual SpatialForceVector externalForce()
        {
            SFV out;
//            if( isBase() )
//            {
//                // return gravity
//                out[4] = -9.8; // y-up
//            }
            return out;
        }

        
		virtual Body* parent( void )
		{
			return parent_;
		}
        
		virtual const Body* parent( void ) const
		{
			return parent_;
		}
        
        virtual void setParent( Body* proximalBody )
        {
            parent_ = proximalBody;
        }

        virtual void setJoint( Joint* proximalJoint ) 
        {
            joint_ = proximalJoint;
        }

        bool isBase( void ) const
		{ 
			return (parent_ == NULL); 
		}
		
		Joint* joint( void )
		{
			return joint_;
		}
        
		const Joint* joint( void ) const
		{
			return joint_;
		}
		
	protected:
        Robot* robot_;
		Body* parent_;
        Joint* joint_;  //< Proximal joint
        SpatialInertia inertia_;
    };
	
}

#endif
