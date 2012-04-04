 ///
/// \file OdeRobot.hpp
/// \brief Concrete classes that represent rigid-bodies and their 
/// constraints (joints) that wrap ODE objects.
///
/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.
///

#ifndef TAU_ODEROBOT_HPP_
#define TAU_ODEROBOT_HPP_

#include "robot.hpp"

#include <cassert>
#include <map>

namespace tau
{
    class OdeRobot;
    class OdeBody;
    
    class OdeJoint : public Joint
    {
        friend class OdeBody;
        friend class OdeRobot;
    public:
        OdeJoint( OdeRobot* robot, dJointID aJointID );
        
        virtual ~OdeJoint() 
        {
            // OdeJoint does not own any of its pointers
        }
        
        virtual SMV spatialVelocityAcrossJoint() = 0;

        virtual MatrixNxN motionSubspace( void ) { return m_S; }

        virtual MatrixNxN constraintSubspace() = 0;

        virtual const XForm& treeXForm() const { return m_treeXForm; }

        virtual XForm& treeXForm()
        {
             return m_treeXForm;
        }
        
        virtual XForm xform() const = 0;

        virtual Body* body();
        
        virtual const Body* body() const;
        
        virtual unsigned int stateSize() const = 0;

        virtual void q( int index, Scalar state ) = 0;
        virtual double q( int index ) const = 0;
        virtual VectorN q() const = 0;
        
        /// The rate of change of the joint.
        ///   stateSize()
        virtual void dq( int index, Scalar state  ) = 0;
        virtual double dq( int index ) const = 0;
        virtual VectorN dq() const = 0;
        
        /// The 2nd derivative of the joint. Interpretted as the desired 
        /// rate of change of the joint for inverse dynamics.
        ///   stateSize()
        virtual void ddq( int index, Scalar state ) = 0;
        virtual double ddq( int index ) const = 0;   
        virtual VectorN ddq() const = 0;

        dJointID getOdeJointID() { return m_jointID; }
    protected:
        /// Attaches the given OdeBody to this joint as the joint's distal body.
        /// Distal body and joint share the same index.
        void associateDistalBody( OdeBody* distalBody );

        /// Returns the proximal (upstream) body attached to this joint.
        dBodyID odeProximalBody();

        /// Returns the distal (downstream) body attached to this joint.
        dBodyID odeDistalBody();

        /// Returns the rotation from the world (in ODE terms) frame to the proximal body.
        /// Most useful during construction, when it is assumed that q = 0, so joint
        /// xform's can be ignored (as they are all identity).
        Matrix3x3 proximalBody_from_world();

        /// Returns the rotation from the world (in ODE terms) frame to the distal body.
        /// Most useful during construction, when it is assumed that q = 0, so joint
        /// xform's can be ignored (as they are all identity).
        Matrix3x3 distalBody_from_world();

        /// Returns the anchor of the joint that is proximal to this
        /// joint ( \f$ \lambda(i) \f$ ) in the world (in ODE terms) coordinates.
        /// If there is no such joint (i.e., if the proximal body is the base), the
        /// then the position of the root body is returned.
        Vector3 proximalJointAnchor_in_world();

        /// Returns the anchor of this joint in world (in ODE terms) coordinates.
        Vector3 jointAnchor_in_world();

        OdeRobot*   m_robot;
        dJointID    m_jointID;

        XForm       m_treeXForm; //< /f$ X_T(i) = {}^{\lambda(i),i}X_{\lambda(i)} /f$ The "tree" transform, from the parent body to the joint's anchor.
        MatrixNxN   m_S; //< motion subspace, subclasses expected to populate appropriately
    };
    
    
	/// A revolute (or hinge) joint allows rotation only around a single axis
	/// which is fixed relative to the parent body.
	class OdeRevoluteJoint : public OdeJoint
	{
	public:
        OdeRevoluteJoint( OdeRobot* robot, dJointID jointID );

        virtual MatrixNxN constraintSubspace( void );
        
        virtual SMV spatialVelocityAcrossJoint()
		{
			return SMV( motionSubspace() * dq(0) );
		}

        virtual XForm xform() const;

        virtual unsigned int stateSize() const
        {
            return 1;
        }
        
        virtual void applyComputedTorque()
        {
            Scalar tau = getComputedTorque()[0];
            //errorLog() << "XXYYZZ: ODE Joint (" << m_jointID << ") applying torque: " << tau << "\n";

//            Scalar max = 1e10;
//            if( tau != tau ) tau = 0;
//            if( tau > max ) tau = max;
//            if( tau < -max ) tau = -max;
            dJointAddHingeTorque( m_jointID, - tau );
        }

        virtual void q( int index, Scalar state )
        {
            assert( index == 0 );
            m_override = true;
            m_override_q = state;
        }
        virtual double q( int index ) const;
        virtual VectorN q() const { VectorN out(1); out(0) = q(0); return out; }
        
        /// The rate of change of the joint.
        ///   stateSize()
        virtual void dq( int index, Scalar state )
        {
            assert( index == 0 );
            m_override = true;
            m_override_dq = state;
        }

        virtual double dq( int index ) const;
        virtual VectorN dq() const
        {
            VectorN out(1); 
            out(0) = dq(0);
            return out;
        }
        
        /// The 2nd derivative of the joint. Interpretted as the desired 
        /// rate of change of the joint for inverse dynamics.
        ///   stateSize()
        virtual void ddq( int index, Scalar state ) { assert( index==0 ); m_ddq = state; }
        virtual double ddq( int index ) const { assert( index==0 ); return m_ddq; } 
        virtual VectorN ddq() const { VectorN out(1); out(0) = m_ddq; return out; }

        virtual ~OdeRevoluteJoint() 
        {
            
        }
        
    protected:
        /// Returns the axis of the joint relative to the ODE Body's frame.
        ///
        /// TODO -- is the "body" frame really the right frame for this???
        /// this frame we want is at the proximal joint anchor, so if q=0, J_T = I
        Vector3 localAxis()
        {
            double x = 0;
            return Vector3( x/x, x/x, x/x ); // make sure this isn't called
            Vector3 axis;
            const dReal* r = dBodyGetRotation( odeProximalBody() );
            Matrix3x3 local_from_world; // r transposed to invert
            local_from_world << 
            r[0], r[3], r[6],
            r[1], r[4], r[7],
            r[2], r[5], r[8];
            dVector3 axisWorldOde;
            dJointGetHingeAxis( m_jointID, axisWorldOde );
            Vector3 axisWorld;
            axisWorld << axisWorldOde[0], axisWorldOde[1], axisWorldOde[2];
            axis = local_from_world * axisWorld;
            return axis;
        }
        
        // TODO
        Vector3 localAnchor()
        {
            Vector3 anchor;
            dVector3 dvec;
            dJointGetHingeAnchor( m_jointID, dvec );
            
            //dvec is in world coordiants, needs to be in proximal body local
            return anchor;
        }
        
    private:
        /// Override is a hack to support "speculative" kinematic motion.
        bool m_override;
        Scalar m_override_q;
        Scalar m_override_dq;
        Scalar m_ddq;
        Scalar m_torque;
	};
    

	/// Body is a rigid-body (aka, link or segment) with mass that can be 
	/// connected to other such bodies by Joints.
	class OdeBody : public Body
	{
        friend class OdeJoint;
	public:
        // Create a body and add it to the given \a robot.
        // This creation is responsible for correctly setting the body's COM
        // and inertia matrix.
        // If this body is the root, it's Frame is it's own COM,
        // if it is not the root, it's Frame is it's proximal joint's anchor.
        OdeBody( OdeRobot* robot, dBodyID odeBodyID );
               
        virtual ~OdeBody();
        
		/// Returns the parent, or NULL if this body is the base.
		/// Usually written as \f$ \lambda(i) \f$ for this body $i$.
		/// Parent is set when a joint is attached.
		virtual Body* parent( void )
        {
            return m_parent;
        }
        
		/// Returns the parent, or NULL if this body is the base.
		/// Usually written as \f$ \lambda(i) \f$ for this body $i$.
		/// Parent is set when a joint is attached.
		virtual const Body* parent( void ) const 
        {
            return m_parent;
        }
		
		/// Returns true if this body represents the fixed base.
        virtual bool isBase( void ) const
        {
            return m_parent == NULL;
        }
		
        /// Returns the joint linking this body to this body's parent, i.e.,
        /// the upstream or proximal joint.
		/// Usually written as \f$ Ji \f$ for this body \f$ i \f$.
		virtual Joint* joint( void )
        {
            return m_joint;
        }
        
		/// Returns the joint linking this body to this body's parent.
		/// Usually written as \f$ Ji \f$ for this body \f$ i \f$.
		virtual const Joint* joint( void ) const 
        {
            return m_joint;
        }
        
        /// Returns the joint linking this body to this body's parent, i.e.,
        /// the upstream or proximal joint.
        /// Usually written as \f$ Ji \f$ for this body \f$ i \f$.
        virtual OdeJoint* odeJoint( void )
        {
            return m_joint;
        }

        /// Returns the joint linking this body to this body's parent.
        /// Usually written as \f$ Ji \f$ for this body \f$ i \f$.
        virtual const OdeJoint* odeJoint( void ) const
        {
            return m_joint;
        }

        /// Store the given \a proximalJoint as associated with this OdeBody.
        virtual void setJoint( Joint* proximalJoint )
        {
            OdeJoint* oj = dynamic_cast< OdeJoint* >( proximalJoint );
            if( oj )
            {
                associateJoint( oj );
            }
        }
		
        /// Sets the interally cached rigid-body inertia relative to the body frame (generally not 
        /// the space as the COM frame).
        /// \note This should not be used to change ODE's Body's inertia properties!
        virtual void setInertia( const SpatialInertia& inertia )
        {
            m_inertia = inertia;
        }
        
        /// Provides the spatial inertia of this body in the body's frame.
        /// If subclasses don't natively use the SpatialInertia, they should cache one for 
        /// better performance.
        virtual SpatialInertia inertia() const
        {
            return m_inertia;
        }
        
        /// Retrieves the total external forces on this body, in then base frame,
        /// that should be compensated for by the inverse dynamics calculations.
        virtual SpatialForceVector externalForce()
        {
            //TODO: This shuold be set-able by the containing application
            return SFV( Vector6::Zero() );
        }

        /// Sets the underlying ODE Body to have a state that matches the position and
        /// velocity of this tau::OdeBody.  Generally the tau body was computed, e.g.,
        /// via kinematics based on the reduced coordinates.
        void setOdeState();

        dBodyID getOdeBodyID() { return m_bodyID; }
    private:

        /// Associates the joint proximal to this body.
        virtual void associateJoint( OdeJoint* proximalJoint )
        {
            m_joint = proximalJoint;
        }

        OdeRobot* m_robot;
        dBodyID m_bodyID;
        OdeBody* m_parent;
        OdeJoint* m_joint; //< Proximal joint, if this is body i, this is joint i.
        
        SpatialInertia m_inertia;
	};

    /// OdeRobot wraps an interconnected set of ODE bodies and joints to make
    /// a Robot for control with computed torque.
    class OdeRobot : public Robot
    {
        friend class OdeJoint;
        friend class OdeBody;
    public:
        typedef std::map< dBodyID, OdeBody* > BodyMap;

        /// Recursively create the  OdeRobot's   OdeBody and   OdeJoint by descending
        /// through the given dBodyID.
        /// The robot's state must be set to all zeros-- ie. in the zero configuration.
        /// Currently, the rootBody is assumed fixed (cannot move).
        /// To meet this constraint in ODE, use dJointCreateFixed() and dJointSetFixed()
        OdeRobot( dBodyID rootBody );  // todo -- add flag for fixed root or not

        /// Apply the torque computed by solveInverseDynamics() to each joint
        /// in the Robot.
        void applyComputedTorque();

        VectorN getComputedTorqueForJointID( dJointID jointID )
        {
            OdeJoint* joint = getJointFromOdeID( jointID );
            if( joint )
            {
                return joint->getComputedTorque();
            }
            else
            {
                return VectorN(3);
            }
        }

        /// Sets the contained ODE bodies to the state stored in this robot.
        /// Generally only should be called after solveKinematics() or similar.
        /// Note that this is much more invasive to ODE than applyComputedTorque,
        /// as setOdeState() sets the full state of the ODE bodies, entirely ignoring
        /// their current state.
        void setOdeState();

        /// Returns the Body corresponding to the given ODE dBodyID.  Returns NULL if
        /// no corresponding body is part of this   Robot.
        OdeBody* getBodyFromOdeID( dBodyID argBody );

        /// Returns the Joint corresponding to the given ODE dJointID.  Returns NULL if
        /// no corresponding joint is found.
        OdeJoint* getJointFromOdeID( dJointID argJoint );

        /// Returns the OdeJoint with the given index.  Identical to Robot::joint( int )
        /// except that this returns the OdeJoint rather than the superclass.
        OdeJoint* odeJoint( unsigned int index );

        /// Returns the OdeJoint with the given index.  Identical to Robot::joint( int )
        /// except that this returns the OdeJoint rather than the superclass.
        const OdeJoint* odeJoint( unsigned int index ) const;

        /// Returns the OdeBody with the given index.  Identical to Robot::body( int )
        /// except that this returns the OdeBody* rather than the superclass.
        OdeBody* odeBody( unsigned int index );

        /// Returns the OdeBody with the given index.  Identical to Robot::body( int )
        /// except that this returns the OdeBody* rather than the superclass.
        const OdeBody* odeBody( unsigned int index ) const;

    private:
        /// Create and return a new OdeJoint, attached to this OdeRobot.
        /// Note that this is not a recursive operation, just the one joint
        /// will be created and added to this OdeRobot.
        OdeJoint* addOdeJoint( dJointID odeJointID );

        /// Recursively descend the ODE bodies to build the robot, starting at the given
        /// \a body and assuming that \a parentFrame provides the transform from the
        /// root (aka, world or base frame) to the parent body of \a body.
        void addOdeBodyRecursive( dBodyID body, OdeJoint* proximalJoint );
        
        dWorldID m_world;

        /// BodyMap holds the mapping between ODE dBodyID's and our Body pointers.
        /// This could be implemented by using indexes into Robot::bodies instead..
        BodyMap m_bodyMap;
    };
    
    /// Returns the world coordinates of the (first) anchor of the given joint.
    /// A zero vector is returned if the joint type is unsupported or if the joint
    /// type doesn't have an anchor (e.g., fixed or prismatic)
    Vector3 getJointAnchorInWorld( dJointID joint );    
    
    /// Returns a string showing the structure of the ODE tree (following distal links).
    std::string dumpOdeTree( dBodyID root, int depth = 1 );
}

#endif
