///
/// \file tau.hpp
/// \brief Spatial algebra and inverse dynamics library
///
/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.
///

#ifndef TAU_HPP_
#define TAU_HPP_

#include "TauSystemIncludes.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"

//#include <cmath>
//#include <algorithm>
#include <iostream>

#ifndef TAU_PI
/// Force decelaration of pi for high precision.
#define TAU_PI (3.14159265358979323846264338328)
#endif

#ifndef TAU_PI_OVER_2
#define TAU_PI_OVER_2 (1.57079632679489661923132169164)
#endif

/// \mainpage The Tau Library: Computed Torque Control using Featherstone's Newton-Euler Inverse Dynamics Algorithm
/// \section motivation Motivation
/// Computed torque control theorectically offers an excellent method for the 
/// control of articulated characters and simulated robots.  Despite the relative
/// simplicity of the algorithm, there really aren't any free, open-source 
/// libraries.  
/// 
/// This project aims to provide a "drop-in" inverse dynamics library for 
/// the Open Dynamics Engine (ODE) physics library.  The primary objective of 
/// the Tau library is to provide a practical and easy-to-use library for
/// controlling articulated bodies for animation and simulated robotics.  
/// On-line control is not a current use-case, so speed and memory optimizations
/// are generally secondary to clarity, extensibility and simplicity.
///
/// \section dependencies Dependicies
/// The Tau library uses the excellent Eigen linear algebra library 
/// (see http://eigen.tuxfamily.org/ ).  The boost
/// unit test libraries are necessary to compile the unit tests.
///
/// \section components Components
/// Tau is made up of three parts: a spatial algebra library (tau.hpp), the
/// robot definition classes (rigid Body, Joint and SpatialMass) (robot.hpp) 
/// and the ODE adapters (tauOde.hpp).
///
/// All components are implemented as header-only libraries, so no linking is
/// required.  All declarations are contained within the namespace "tau", 
/// except the unit tests, which use the global namespace.  Preprocessor defines
/// are used for constant values (pi, pi/2, etc) with the prefix TAU_.
/// 

/// Catch-all namespace for the tau library.
namespace tau
{
	/// Change this typedef to set the size of scalars.  (Only double has been tested)
    typedef double Scalar;
	/// 3D Vector
	typedef Eigen::Matrix< Scalar, 3, 1 > Vector3;
	/// 6D Vector
	typedef Eigen::Matrix< Scalar, 6, 1 > Vector6;
    /// Arbitrary Length Vector
    typedef Eigen::Matrix< Scalar, Eigen::Dynamic, 1 > VectorN;
	/// 3x3, 9-elem Matrix
	typedef Eigen::Matrix< Scalar, 3, 3 > Matrix3x3;
	/// 6x6, 36-elem Matrix
	typedef Eigen::Matrix< Scalar, 6, 6 > Matrix6x6;
	/// 6xN variable sized Matrix
    typedef Eigen::Matrix< Scalar, Eigen::Dynamic, Eigen::Dynamic > MatrixNxN;
	/// Quaternion
	typedef Eigen::Quaternion<Scalar>     Quaternion;
	/// Affine (aka rigid body) transformation
	typedef Eigen::Transform<Scalar, 3>   AffineTransform;
	/// Simple translation along a vector.
	typedef Eigen::Translation<Scalar, 3> Translation;

    enum { X, Y, Z, W };
	
    class Point;
    class SpatialVector;
    class SpatialMotionVector;
    class SpatialForceVector;
    class SpatialInertia;
    class XForm;

    /// Returns the 3x3 identity matrix.
	Matrix3x3 eye( void );
	
	/// Returns the 3x3 matrix of all zeros.
	Matrix3x3 zero( void );
    
    /// Returns the 3x3 skew-symmetric matrix derived from vector r.
    Matrix3x3 skewSym( const Vector3& r );
    
    /// Returns a 3x3 rotation matrix representing a rotation of \a argRadians
    /// around the x-axis.
    Matrix3x3 rotX( Scalar argRadians );
    
    /// Returns a 3x3 rotation matrix representing a rotation of \a argRadians
    /// around the y-axis.
    Matrix3x3 rotY( Scalar argRadians );
    
    /// Returns a 3x3 rotation matrix representing a rotation of \a argRadians
    /// around the y-axis.
    Matrix3x3 rotZ( Scalar argRadians );
	
	/// Returns the rotation matrix representing a rotation of angle \a radians
	/// around the \a axis.  Based on the Rodrigues' rotation formula.
	Matrix3x3 rotFromAxisAngle( const Vector3& axis, Scalar radians );    

    /// Returns the rotoation matrix representing a rotation that takes
    /// vector \a from to vector \a to.
    Matrix3x3 rotFromTwoVectors( const Vector3& from, const Vector3& to );
    
    /// Provides standard output.
    std::ostream& operator<<( std::ostream& out, const SpatialVector& arg );

    /// XForm composition, standard matrix multiplication.
    XForm operator*( const XForm& left, const XForm& right );
    
    /// Dump an XForm to ostream
    std::ostream& operator<<( std::ostream& out, const XForm& arg );
    
    /// Dump spatial inertia out to ostream
    std::ostream& operator<<( std::ostream& out, const SpatialInertia& arg );

    /// The vector from aFrom to aTo
	Vector3 operator-( const Point& aTo, const Point& aFrom );

    /// Element-wise multiplication by scalar.
	SpatialMotionVector operator*( Scalar aFactor, const SpatialMotionVector& aVec );
    
	/// Element-wise multiplication by scalar.
	SpatialMotionVector operator*( const SpatialMotionVector& aVec, Scalar aFactor );
        
    /// Element-wise multiplication by scalar.
	SpatialForceVector operator*( Scalar aFactor, const SpatialForceVector& aVec );
	
	/// Element-wise multiplication by scalar.
	SpatialForceVector operator*( const SpatialForceVector& aVec, Scalar aFactor );
	
    /// Stream error reporting method
    std::ostream& errorLog( void );
    
	/// Represents a 3D point.
	class Point
	{
		friend Vector3 operator -( const Point& aTo, const Point& aFrom );
	public:
		Point();

		/// Create point at the given position (x,y,z)
		Point( Scalar aX, Scalar aY, Scalar aZ );
		
		/// Access the elems of the point
		Scalar operator[]( int aIdx ) const;
		
		/// Access and modify the elems of the point
		Scalar& operator[]( int aIdx );

	private:
		Vector3 data_;
	};

    
    /// Abstract super-class handling the behavior of spatialvector
    /// Throughout, the rotation component is first (0,1,2) and the
    /// position component is second (3,4,5)
    class SpatialVector 
    {
    public:
        SpatialVector( void )
        {
            data_.setZero();
        }
		
        /// Build SpatialVector from it's elements, angular first.
        SpatialVector( Scalar a0, 
                       Scalar a1, 
                       Scalar a2, 
                       Scalar a3, 
                       Scalar a4, 
                       Scalar a5 )
        {
            data_[0] = a0;
            data_[1] = a1;
            data_[2] = a2;
            data_[3] = a3;
            data_[4] = a4;
            data_[5] = a5;
        }
        
		/// Builds a 6D spatial vector by stacking two 3D vectos.
		/// Generally, aFirst is the angular component and aSecond is
		/// the linear component.
        SpatialVector( Vector3 aFirst, Vector3 aSecond )
        {
            data_.start<3>() = aFirst;
            data_.end<3>() = aSecond;
        }
        
		/// Build a SpatialVector from the given 6D vector, 
		/// assumes angular components come first.
        SpatialVector( const Vector6& aM )
        : data_( aM )
        {
            // Noop
        }
        
        const Vector6& asVector6() const
        {
            return data_;
        }
        
        Vector6 asVector6() 
        {
            return data_;
        }
        
        operator Vector6() const
        {
            return asVector6();
        }

		/// Sets this vector to all zeros.
		void setZero()
		{
			data_.setZero();
		}
        
		/// Provides direct access to the elems.
		const Scalar operator[] ( int aIndex ) const
		{
			return data_[aIndex];
		}
		/// Provides direct access for modification of the elems.
		Scalar& operator[] ( int aIndex )
		{
			return data_[aIndex];
		}

		/// Returns a copy of the first 3d vector component, generally the rotational component.
        Vector3 first( void ) const
        {
            return data_.start<3>();
        }

		/// Returns a copy of the second 3d vector component, generally the translational component.
		Vector3 second( void ) const
        {
            return data_.end<3>();
        }
		
		/// Returns the cross-product matrix for this spatial vector.
		/// Overrides provide specific implementation for subclasses.
		virtual Matrix6x6 skewSym( void ) const = 0;
        
        /// Copies this spatial vector to the given array, assuming that out has
        /// at least six elements.
        template< typename ScalarOutT >
        void copyToArray( ScalarOutT* out )
        {
            for( size_t i=0; i<data_.size(); ++i ) *(out+i) = data_[i];
        }

		/// Fills out with the first 3d vector.
		/// \param out is a pointer to an array with at least three elements.
        template< typename ScalarOutT >
        void copyFirstToArray( ScalarOutT* out )
        {
            for( size_t i=0; i<3; ++i ) *(out+i) = data_[i];
        }
        
		/// Fills out with the second 3d vector.
		/// \param out is a pointer to an array with at least three elements.
        template< typename ScalarOutT >
        void copySecondToArray( ScalarOutT* out )
        {
            for( size_t i=0; i<3; ++i ) *(out+i) = data_[i+3];
        }

		/// Standard output method. 
        friend std::ostream& operator<<( std::ostream& out, const SpatialVector& arg );
    protected:
        virtual ~SpatialVector() {}

        /// A six element vector containing three rotational components, then three linear components
        Vector6 data_;
    };

    
    /// A 6D spatial vector representing a combined angular and linear motion,
    /// e.g., angular and linear velocity, or angular and linear acceleration.
    class SpatialMotionVector : public SpatialVector
    {
    public:
        SpatialMotionVector() 
        : SpatialVector() 
        {
            // Noop
        }
        
		/// Builds from the provided elements, angular first.
        SpatialMotionVector( Scalar a0, 
                      Scalar a1, 
                      Scalar a2, 
                      Scalar a3, 
                      Scalar a4, 
                      Scalar a5 )
        : SpatialVector( a0, a1, a2, a3, a4, a5 )
        {
            // Noop
        }
        
		/// Builds from the two 3D vectors, omega as the angular component, vel as the linear.
        SpatialMotionVector( const Vector3& aOmega, const Vector3& aVel )
        : SpatialVector( aOmega, aVel )
        {
            // Noop
        }
        
		/// Builds from the 6D vector, assuming first three elems are the angular component.
        SpatialMotionVector( const Vector6& aM )
        : SpatialVector( aM )
        {
            // Noop
        }
        
        /// Returns a 6x6 skew-symmetric matrix based on this vector.
        /// This implements the cross-product that is specific to spatial motion vectors.
		virtual Matrix6x6 skewSym( void ) const
		{
			// skewSym(v1:3) , 0
			// skewSym(v4:6) , skewSym(v1:3)
			Matrix6x6 out;
			Matrix3x3 skewOmega = tau::skewSym( first() );
			Matrix3x3 skewVel   = tau::skewSym( second() );
			
			out << skewOmega, Matrix3x3::Zero(),
			/*  */ skewVel, skewOmega;
			return out;
		}
        
		/// Copies the angular (first) 3D vector to out.
		/// \param out is a pointer to an array with at least three elements.
        template< typename ScalarOutT >
        void copyAngularToArray( ScalarOutT* out )
        {
            copyFirstToArray( out );
        }

		/// Copies the linear (second) 3D vector to out.
		/// \param out is a pointer to an array with at least three elements.
        template< typename ScalarOutT >
        void copyLinearToArray( ScalarOutT* out )
        {
            copySecondToArray( out );
        }

        /// Returns the derivative of the quaternion representation
        /// of the angular velocity of this motion vector.
        template< typename ScalarOutT >
        void getDerivQuaternion( ScalarOutT* out )
        {
            throw "NYI";
        }
		
		/// Element-wise multiplication by scalar.
		friend SpatialMotionVector operator*( Scalar aFactor, const SpatialMotionVector& aVec );
		/// Element-wise multiplication by scalar.
		friend SpatialMotionVector operator*( const SpatialMotionVector& aVec, Scalar aFactor );

    };
	/// Short alias for SpatialMotionVector.
	typedef SpatialMotionVector SMV;
    
    SpatialMotionVector operator+( const SpatialMotionVector& a,
                                   const SpatialMotionVector& b );

    /// A 6D spatial vector representing a combined torque and force.
    class SpatialForceVector : public SpatialVector
    {
        /// Element-wise multiplication by scalar.
		friend SpatialForceVector operator*( Scalar aFactor, const SpatialForceVector& aVec );
		/// Element-wise multiplication by scalar.
		friend SpatialForceVector operator*( const SpatialForceVector& aVec, Scalar aFactor );
    public:
		SpatialForceVector() 
        : SpatialVector() 
        {
            // Noop
        }
        
        /// Build SpatialVector from it's elements, angular first.
        SpatialForceVector( Scalar a0, 
							Scalar a1, 
							Scalar a2, 
							Scalar a3, 
							Scalar a4, 
							Scalar a5 )
        : SpatialVector( a0, a1, a2, a3, a4, a5 )
        {
            // Noop
        }
        
		/// Builds from the two 3D vectors, aMoment as the angular (torque) component, vel as the linear.
        SpatialForceVector( Vector3 aMoment, Vector3 aForce )
        : SpatialVector( aMoment, aForce )
        {
            // Noop
        }
		
		/// Builds from the 6D vector, assuming first three elems are the angular (torque) component.
        SpatialForceVector( const Vector6& aM )
        : SpatialVector( aM )
        {
            // Noop
        }
		
        /// Returns a 6x6 skew-symmetric matrix based on this vector.
        /// This implements the cross-product that is specific to spatial force vectors.
		virtual Matrix6x6 skewSym( void ) const
		{
			Matrix6x6 out;
			Matrix3x3 ssft = tau::skewSym( first() ).transpose();
			out << ssft, tau::skewSym( second() ).transpose(),
			/*  */ Matrix3x3::Zero(), ssft;
			return - out;  // note negation
		}
    };
	/// Short alias for SpatialForceVector.
	typedef SpatialForceVector SFV;

    /// Element-wise addition of SpatialForceVector
    SpatialForceVector operator+( const SpatialForceVector& a, const SpatialForceVector& b );
    
    /// SpatialInertia, aka Rigid Body Inertia, represents the inertia of a rigid body.
    class SpatialInertia
    {
        friend std::ostream& operator<<( std::ostream& out, const SpatialInertia& arg );
    public:
        /// Creates a SpatialInertia with scalar mass of 1.0, and it's COM at 0,0,0 in
        /// the body frame, and with an inertia tensor of the identity.
        SpatialInertia();
        
        /// Constructs a SpatialInertia (aka, rigid-body inertia)
        /// with scalar mass of \a mass, center-of-mass located at \a com,
        /// and with inertia matrix specified by the six elements of \a inertia.
        /// To convert a symmetric, 3x3 inertia matrix to the form of \a inertia,
        /// use   ltToVector().
        SpatialInertia( Scalar mass, const Vector3& com, const Vector6& inertia );

        /// Returns a 6x6 matrix representation of this spatial inertia.
        Matrix6x6 toMatrix6x6() const;
        
        /// Returns the 3x3 inertia matrix at the center of mass.
        Matrix3x3 inertiaMatrix() const;
        
        /// Returns the scalar mass of the system.
        const Scalar& m() const { return m_mass; }
        
        /// Returns the vector from the system's frame to the system's center of mass.
        const Vector3& h() const { return m_com; }
        
        /// Returns the 3x3 inertia matrix around the center of mass.
        Matrix3x3 I() const { return inertiaMatrix(); }
        
    private:
        /// The total scalar mass.
        Scalar m_mass;
        
        /// The position of the CoM in the frame.  Generally, the frame is
        /// the   Body frame.
        /// h in Featherstone.
        Vector3 m_com;
        
        /// 3x3 symmetric rotational inertia matrix about the CoM.
        /// Expanded, it becomes:
        /// m_I[0] m_I[1] m_I[3]
        /// m_I[1] m_I[2] m_I[4]
        /// m_I[3] m_I[4] m_I[5]
        Vector6 m_I;
    };

    /// Apply a spatial inertia to a motion vector to map it to a force vector.
    SFV operator*( const SpatialInertia& I, const SMV& v ); 

    /// Returns a Vector6 that holds the lower-triangular elements of the 3x3 matrix \a m using 
    /// the pattern:
    /// m[0] 
    /// m[1] m[2] 
    /// m[3] m[4] m[5]
    Vector6 ltToVector( const Matrix3x3& m );
    
    /// Construct a symmetric 3x3 Matrix using the given elements, as:
    /// v[0] v[1] v[3]
    /// v[1] v[2] v[4]
    /// v[3] v[4] v[5]
    Matrix3x3 ltFromVector( const Vector6& v );

    /// Plucker transform for spatial vectors.
    /// The transform from A to B for motion vectors is written \f$ {}^{B}X_{A} \f$ , and
    /// for force vectors as \f$ {}^{B}X_{A}^{*} \f$
    /// The transform is "natively" a motion transform, force 
    /// transforms are computed at apply() time, but user's don't need to be aware of this,
    /// the correct transform will be applied by operator overloading.
    /// Internally, the XForm is stored as a translation and a rotation. 
    class XForm
    {
        friend XForm operator*( const XForm& left, const XForm& right );
        friend std::ostream& operator<<( std::ostream& out, const XForm& arg );
    public:
        /// Default constructor creates an identity transform.
        XForm( void )
        : m_E( Matrix3x3::Identity() ), m_r( Vector3::Zero() )
        {
            // Noop
        }
        
        XForm( const XForm& other )
        : m_E( other.m_E ), m_r( other.m_r )
        {
            // Noop
        }
        
        /// Construct from a translation and rotation.
        /// The XForm applys the translation first, then the rotation.
        XForm( const Matrix3x3& argRotation, const Vector3& argTranslation )
        : m_E( argRotation ), m_r( argTranslation )
        {
            // Noop
        }
        
        XForm& operator=( const XForm& other )
        {
            this->m_E = other.m_E;
            this->m_r = other.m_r;
            return *this;
        }
        
        const Matrix3x3& E() const
        {
            return m_E;
        }
        
        const Vector3& r() const 
        {
            return m_r;
        }
        
        /// Returns the inverse XForm, i.e, if this transforms from frame A to B, 
        /// then the returned XForm transforms from frame B to frame A.
        XForm inverse() const
        {
            return XForm( m_E.transpose(), - m_E * m_r );
        }
        
        /// Transform the given spatial motion vector by this plucker xform.
        SpatialMotionVector apply( const SpatialMotionVector& aV )
        {
            return SpatialMotionVector( m_E * aV.first(), 
                                        m_E * ( aV.second() - m_r.cross(aV.first()) ) );
        }

        /// Apply this plucker transform to the given force vector.
        SpatialForceVector apply( const SpatialForceVector& aF )
        {
            return SpatialForceVector( m_E * ( aF.first() - m_r.cross(aF.second()) ),
                                       m_E * aF.second() );
        }
        
        /// Apply this plucker transform to the given spatial inertia (RBI).
        /// Equivalent to:
        /// \f$ X^{*}\hat{I}X^{-1} \f$
        SpatialInertia apply( const SpatialInertia& aI )
        {
            const Scalar&  m = aI.m();
            const Vector3& h = aI.h();
            const Matrix3x3 I = aI.I();
            
            Matrix3x3 tmp = I + skewSym(m_r) * skewSym(m_r) * skewSym(h)
                              + skewSym(h - m*m_r) * skewSym(m_r); 
                                          
            return SpatialInertia( m,
                                   m_E * ( h - m * m_r ),
                                   ltToVector( m_E * tmp * m_E.transpose() ) );
        }

 		/// Returns the result of applying the inverse of this transform to the 
		/// given vector. 
        SpatialMotionVector invApply( const SpatialMotionVector& aV )
        {
            return SpatialMotionVector( m_E.transpose() * aV.first(),
                                        m_E.transpose() * aV.second() 
                                        + m_r.cross( m_E.transpose() * aV.first() ) );
        }
        
		/// Returns the result of applying the inverse of this transform to the 
		/// given vector. 
        SpatialForceVector invApply( const SpatialForceVector& aF )
        {
            return SpatialForceVector( m_E.transpose() * aF.first() 
                                       + m_r.cross( m_E.transpose() * aF.second() ),
                                       m_E.transpose() * aF.second() );
        }
        
        /// Applies the inverse transform to the given rbi/spatial inertia \a aI.
        /// Equivalent to:
        /// \f$ X^{T} \hat{I} X \f$
        SpatialInertia invApply( const SpatialInertia& aI )
        {
            const Scalar&  m = aI.m();
            const Vector3& h = aI.h();
            const Matrix3x3 I = aI.I();
        
            return SpatialInertia( m,
                            m_E.transpose() * h + m*m_r,
                            ltToVector( m_E.transpose()*I*m_E 
                                - skewSym(m_r) * skewSym(m_E.transpose()*h)
                                - skewSym(m_E.transpose()*h + m*m_r) * skewSym(m_r) ) );
 
        }
        
        /// Returns true if \a that XForm represents exactly the same transform as this.
        bool operator==( const XForm& that ) const 
        {
            return (m_E == that.m_E) && (m_r == that.m_r);
        }
        
		/// Provides const access to the underlying Eigen matrix.
        Matrix6x6 asMatrix6x6() const
        {
            Matrix6x6 out = Matrix6x6::Zero();
            out.corner<3,3>(Eigen::TopLeft) = m_E;
            out.corner<3,3>(Eigen::BottomLeft) = - m_E * skewSym( m_r );
            out.corner<3,3>(Eigen::BottomRight) = m_E;
            return out;
        }
        
        /// @name Static construction methods
        /// Methods that build the PluckerXForm from its affine components.
        //@{
        
        /// Creates an identity plucker transform.
        static XForm identity()
        {
            return XForm( Matrix3x3::Identity(), Vector3::Zero() );
        }

        /// Create a plucker transform representing the given rotation.
        static XForm fromRotationMatrix( const Matrix3x3& argRotationMatrix )
        {
            return XForm( argRotationMatrix, Vector3::Zero() );
        }

        /// Create a plucker transform representing the given translation.
        static XForm fromTranslation( const Vector3& argTranslation )
        {
            return XForm( Matrix3x3::Identity(), argTranslation );
        }
        //@}
        
        
    protected:
  
    private:
        Matrix3x3 m_E;
        Vector3 m_r;
    }; // end XForm


} // end namespace tau


#endif /* TAU_HPP_ */
