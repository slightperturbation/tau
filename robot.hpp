/// 
/// \file robot.hpp
/// \brief Abstract classes that represent rigid-bodies and their 
/// constraints (joints).
///
/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.
///

#ifndef TAU_ROBOT_HPP_
#define TAU_ROBOT_HPP_

#include "tau.hpp"

#include <vector>
#include <algorithm>

namespace tau
{
    class Body;
    class Joint;
    class Robot;
    
	/// Joint is the abstract super-class for scleronomic joints (ie, joints
	/// not dependent on time (rheonomic) nor on the derivatives of the 
	/// generalized coordinates (nonholonomic)).
    /// Joint holds its own state information, includeing q, dq and ddq.
    /// Be careful when using a joint to have previously set the q, dq, ddq
    /// values to correct/desired values.
	class Joint
	{
        friend class Robot;
        friend class Body;
	public:
        Joint() : cached_computed_torque( VectorN::Zero(1) ) {}
        virtual ~Joint() {}
        
		/// Returns the spatial velocity across this joint.
		/// In world coordinates, this would be \f$ v_J = v_s - v_p \f$, ie.
		/// the velocity of the sucessor body minus the velocity of the 
		/// preceeding body.  Internally, this is computed using:
		/// \f$ v_J = S(q) \dot{q} \f$
		/// For sceleronomic joints, \f$ S \f$ is constant, so no parameter for
        /// \f$ q \f$ is needed.
		virtual SMV spatialVelocityAcrossJoint() = 0;
        SMV v_J() { return spatialVelocityAcrossJoint(); }
        
        /// \f$ c_J = \mathring{S} \dot{q} \f$
        virtual SMV c_J() { return SMV(); /* zeros */ }

		/// Returns a 6xN matrix, where N is equal to the number of DOFs in 
		/// the joint.  Usually written as \f$ S \f$.
		/// In the most general sense, would depend on q and t, but this class
		/// is restricted to scleronomic joints, so the subspace is fixed for
        /// all times and joint positions.
		virtual MatrixNxN motionSubspace() = 0;
        MatrixNxN S() { return motionSubspace(); }
        
		/// Returns a 6xN matrix, where N is equal to 6 - DOFs of joint.
		/// Usually written as \f$ T \f$.
		/// In the most general sense, would depend on \f$q\f$ and \f$t\f$, 
		/// but this class is restricted to simple joints.
		virtual MatrixNxN constraintSubspace() = 0;
		
		/// Returns the transformation mapping the predecssor's frame \f$F_p\f$
		/// to the location of the joint's anchor \f$F_{\lambda(i), i}\f$.
		///
        /// \f$ X_{T}(i) = {}^{\lambda(i),i}X_{\lambda(i)} \f$ 
        ///
		/// Assumed constant and determined by the geometry of the robot (i.e., 
        /// we only scleronomic joints).
        ///
        /// Distinguish from xform(), which depends on the current state.
        /// Together, xform() and treeXForm() provide the xform from the 
        /// predecessor to the successor body.
        ///   xform() 
		virtual const XForm& treeXForm() const = 0;
        virtual XForm& treeXForm() = 0;
        
        /// Anchor is a psuedonym for the tree transform, tree().
        const XForm& anchor() const { return treeXForm(); }
        XForm& anchor() { return treeXForm(); }
		
		/// Returns the transformation holding the "effect" of the joint, 
        /// and the joint alone (ie., not the anchor/tree transform) for the 
        /// current value of q.
        ///
        /// \f$X_{Ji} = {}^{i}X_{\lambda(i),i} \f$.
        ///
        /// Note that, by construction
        /// \f$ q = 0 \to xform() = I \f$, i.e., the joint transform is   
        /// the identity when \f$ q = 0 \f$.
        ///
        /// Be careful to distinguish from treeXForm, which is constant wrt q.
        ///   treeXForm()
        virtual XForm xform() const = 0;
        
        /// Returns the   Body that is distal to this joint.  
        virtual Body* body() = 0;
        virtual const Body* body() const = 0;
        
        /// Returns the number of state variables required by this joint.
        /// The returned value is the size of the q, dq, and ddq vectors.
        /// (Often the same as then number of DOFs, but not always)
        virtual unsigned int stateSize() const = 0;
        
        /// The position of the joint.
        ///   stateSize()
        virtual void q( int index, Scalar state ) = 0;
        virtual Scalar q( int index ) const = 0;
        virtual VectorN q() const = 0;
        
        /// The rate of change of the joint.
        ///   stateSize()
        virtual void dq( int index, Scalar dstate ) = 0;
        virtual Scalar dq( int index ) const = 0;
        virtual VectorN dq() const = 0;

        /// The 2nd derivative of the joint. Interpretted as the desired 
        /// rate of change of the joint for inverse dynamics.
        ///   stateSize()
        virtual void ddq( int index, Scalar ddstate ) = 0;
        virtual Scalar ddq( int index ) const = 0;   
        virtual VectorN ddq() const = 0;
        
        void setComputedTorque( const VectorN& tau )
        {
            //errorLog() << "JOINT (" << this << ") setting Computed Torque: " << tau << "\n";
            cached_computed_torque = tau;
        }

        /// Returns a vector of size   stateSize() holding the 
        /// computed torques.  Available only after calling   Robot::solveInverseDynamics()
        virtual VectorN getComputedTorque() const 
        { 
            return cached_computed_torque;
        }
        
        virtual void applyComputedTorque()
        {
            assert( false );
        }
    
    protected:
        VectorN cached_computed_torque;  
	};
	
	/// Body is a rigid-body (aka, link or segment) with mass that can be 
    /// connected to other such bodies by   Joint instances.
    /// It's important to note that a Body has a frame (\f$ F_i \f$), but that
    /// this frame is not stored in the Body class.  Rather, the body frame
    /// is computed (relative to the fixed base) by the owning   Robot using
    ///   solveKinmatics().
	class Body
	{
        friend class Robot;
        friend class Joint;
	public:
        Body()
            : cached_body_from_base( XForm::identity() )
        {
            // noop
        }

        virtual ~Body() {}

		/// Returns the parent, or NULL if this body is the base.
		/// Usually written as \f$ \lambda(i) \f$ for this body $i$.
		/// Parent is set when a joint is attached.
		virtual Body* parent() = 0;
		
		/// Returns the parent, or NULL if this body is the base.
		/// Written as \f$ \lambda(i) \f$ for this body $i$.
		/// Parent is set when a joint is attached.
		virtual const Body* parent() const = 0;
        
		/// Returns true if this body represents the fixed base.
        virtual bool isBase() const = 0;
		
		/// Returns the joint linking this body to this body's parent.
		/// Written as \f$ Ji \f$ for this body \f$ i \f$.
		virtual Joint* joint() = 0;
        
		/// Returns the joint linking this body to this body's parent.
		/// Written as \f$ Ji \f$ for this body \f$ i \f$.
		virtual const Joint* joint() const = 0;
        
        /// Sets the joint proximal to this body.
        virtual void setJoint( Joint* proximalJoint ) = 0;
		
        /// Sets the rigid-body inertia relative to the body frame (generally not 
        /// the same as the COM frame).
        virtual void setInertia( const SpatialInertia& inertia ) = 0;
        
        /// Provides the spatial inertia of this body relative to the body frame.
        /// If subclasses don't natively use the SpatialInertia, they should cache one for 
        /// better performance.
        virtual SpatialInertia inertia() const = 0;
        
        /// Retrieves the total external forces on this body, in then base frame,
        /// that should be compensated for by the inverse dynamics calculations.
        virtual SpatialForceVector externalForce() = 0;
        
        /// Provides the XForm that transforms from the frame of the base (root)
        /// body ( \f$ F_0 \f$ ) to the frame of this body (\f$ F_i \f$).
        /// Warning: Only valid after computed, e.g., with   robot::solveKinematics()
        virtual XForm& xForm_body_from_base()
        {
            return cached_body_from_base;
        }
        
        /// Provides the XForm that transforms from the frame of the base (root)
        /// body ( \f$ F_0 \f$ ) to the frame of this body (\f$ F_i \f$).
        /// Warning: Only valid after computed, e.g., with   robot::solveKinematics()
        virtual const XForm& xForm_body_from_base() const
        {
            return cached_body_from_base;
        }

    protected:
        void setXForm_body_from_base( const XForm& arg );
        
        const SMV& spatialVelocity() const
        {
            return cached_spatial_velocity;
        }
        
        void setSpatialVelocity( const SMV& arg )
        {
            cached_spatial_velocity = arg;
        }
        
        const SMV& v() const
        {
            return spatialVelocity();
        }
        
        const SMV& spatialAcceleration() const
        {
            return cached_spatial_acceleration;
        }
        
        void setSpatialAcceleration( const SMV& arg )
        {
            cached_spatial_acceleration = arg;
        }
        
        const SMV& a() const
        {
            return spatialAcceleration();
        }
        
        const SFV& spatialForce() const
        {
            return cached_spatial_force;
        }
        
        void setSpatialForce( const SFV& arg )
        {
            cached_spatial_force = arg;
        }
        
        const SFV& f() const
        {
            return spatialForce();
        }
        
    private:
        XForm cached_body_from_base;
        SMV cached_spatial_velocity;
        SMV cached_spatial_acceleration;
        SFV cached_spatial_force;
	};
    typedef std::vector< Body* > BodyVector;

    
    /// Robot is a collection of Bodies (aka links) connected by Joints.  
    /// The robot class is responsible for computing dynamics and inverse
    /// dynamics over the system.  
    /// The Bodies of the robot are indexed, starting with 0.
    /// The Joints of the robot are indexed, starting with 1.
    /// The zeroth body is considered the fixed base.  (Note that
    /// robots without fixed bases should be modeled with the fixed
    /// ground at index 0, and a six DOF "joint" connecting the ground
    /// the the first Body of the robot.)
    /// The i'th joint connects Body i and its parent.
    /// The Bodies are numbered according to a spanning tree starting at the 
    /// Robot's root, 
    class Robot
    {
        friend class Body;
        friend class Joint;
    public:
        Robot()
        {
            // Noop 
            // Subclasses can be used to require at least a root body
            // or handle creation/deletion
        }

        virtual ~Robot() { }
        
        /// Return the (fixed) base of the robot.  Note that for Robots with
        /// non-fixed bases, this returns the fixed ground.
        Body* root();
        
        /// Returns the Body by index.
        Body* body( unsigned int index );

        /// Returns the Body by index.
        const Body* body( unsigned int index ) const;
                
        /// Returns the index of the given body.  Returns -1 if no such body
        /// is found.
        int bodyIndex( const Body* arg ) const;

        size_t bodyCount() const { return bodies.size(); }

        /// Returns the Joint linking Body i to its parent.
        Joint* joint( unsigned int index );

        /// Returns the Joint linking Body i to its parent.
        const Joint* joint( unsigned int index ) const;
        
        /// Return the Body that is the parent of the Body at index.
        /// So parent(i) is \f$ \lambda(i) \f$.
        Body* parent( unsigned int index );
        
        /// Provides the XForm that transforms from the frame of the base (root)
        /// body ( \f$ F_0 \f$ ) to the frame of the \a index 'th body (\f$ F_i \f$).
        /// Only valid after computed, e.g., with   solveKinematics()
        virtual const XForm& xForm_body_from_base( unsigned int index ) const
        {
            assert( index < bodies.size() );
            // for now, we assume it's available through the body
            return bodies[index]->xForm_body_from_base();
        }
                
        /// Returns a reference to the XForm that transforms from the frame of the base (root)
        /// body ( \f$ F_0 \f$ ) to the frame of the \a index 'th body (\f$ F_i \f$).
        /// This non-const version can be used to set the cached value.
        virtual XForm& xForm_body_from_base( unsigned int index )
        {
            assert( index < bodies.size() );
            // for now, we assume it's available through the body
            return bodies[index]->xForm_body_from_base();
        }

        
        /// Given the state vector \a q and its derivative \a dq, solve the forward 
        /// kinematics for position and velocity of the body frames.
        void solveKinematics( const VectorN& q, const VectorN& dq )
        {
            // TODO -- incorporate into single loop of solveKinematics()
            
            // set state for each body
            size_t stateIdx = 0;
            for( size_t bodyIdx = 0; bodyIdx != bodies.size(); ++bodyIdx )
            {
                Joint* j = bodies[bodyIdx]->joint();
                for( size_t i=0; i < j->stateSize(); ++i )
                {
                    j->q(i, q[stateIdx] );
                    j->dq(i, q[stateIdx] );
                    ++stateIdx;
                }
            }
            solveKinematics();
        }
        
        /// Compute the position, velocity and acceleration of each joint,
        /// given the q, dq and ddq values already set.
        /// Requires one pass through the hierarchy, from the root out to the distal bodies.
        /// Pre: assume joint state (q, dq, ddq are already set).
        /// Pre: assume body at index 0 is the root.
        void solveKinematics( int debugLevel = 0 );
        
        void solveInverseDynamics( const VectorN& q, const VectorN& dq, const VectorN& ddq, int debugLevel = 0 )
        {
            size_t stateIdx = 0;
            for( size_t bodyIdx = 0; bodyIdx != bodies.size(); ++bodyIdx )
            {
                Joint* j = bodies[bodyIdx]->joint();
                for( size_t i=0; i < j->stateSize(); ++i )
                {
                    j->q(i, q[stateIdx] );
                    j->dq(i, dq[stateIdx] );
                    j->ddq(i, ddq[stateIdx] );
                    ++stateIdx;
                }
            }
            solveInverseDynamics( debugLevel );
        }
        
        void solveInverseDynamics( const VectorN& ddq, int debugLevel = 0 )
        {
            size_t stateIdx = 0;
            for( size_t bodyIdx = 0; bodyIdx != bodies.size(); ++bodyIdx )
            {
                Joint* j = bodies[bodyIdx]->joint();
                if( !j ) continue;
                for( size_t i=0; i < j->stateSize(); ++i )
                {
                    j->ddq(i, ddq[stateIdx] );
                    ++stateIdx;
                }
            }
            solveInverseDynamics( debugLevel );
        }
        
        void solveInverseDynamics( int debugLevel = 0 );

        /// Apply the torque computed by solveInverseDynamics to all bodies in Robot.
        void applyComputedTorque()
        {
            assert(false);
        }

        size_t addBody( Body* arg )
        { 
            bodies.push_back( arg ); 
            return bodies.size() - 1; 
        }
        
        BodyVector bodies; 
    };
    
}
#endif
