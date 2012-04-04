/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.


#include "tau.hpp"
#include <Eigen/Geometry>
using namespace tau;

///////////////////////////////////////////////////////////////////////////////
// Free Functions

std::ostream& tau::errorLog( void ) 
{
    return std::cerr; 
}

Vector3 tau::operator-( const Point& aTo, const Point& aFrom )
{
    return Vector3( aTo.data_ - aFrom.data_ );
}

/// Returns the 3x3 identity matrix.
Matrix3x3 tau::eye( void )
{
    return Matrix3x3::Identity();
}

/// Returns the 3x3 matrix of all zeros.
Matrix3x3 tau::zero( void )
{
    Matrix3x3 out;
    out.setZero();
    return out;
}

/// Returns the skew-symmetric matrix derived from vector r.
Matrix3x3 tau::skewSym( const Vector3& r )
{
    Matrix3x3 out(3,3);
    out(0,0) =  0;     out(0,1) = -r[Z]; out(0,2) =  r[Y];
    out(1,0) =  r[Z];  out(1,1) =  0;    out(1,2) = -r[X];
    out(2,0) = -r[Y];  out(2,1) =  r[X]; out(2,2) =  0;
    return out;
}
/// Returns a 3x3 rotation matrix representing a rotation of argRadians
/// around the x-axis.
Matrix3x3 tau::rotX( Scalar argRadians )
{
    Matrix3x3 e(3,3);
    Scalar c = std::cos( argRadians );
    Scalar s = std::sin( argRadians );
    e(0,0) =  1; e(0,1) =  0; e(0,2) =  0;
    e(1,0) =  0; e(1,1) =  c; e(1,2) =  s;
    e(2,0) =  0; e(2,1) = -s; e(2,2) =  c;
    return e;
}

/// Returns a 3x3 rotation matrix representing a rotation of argRadians
/// around the y-axis.
Matrix3x3 tau::rotY( Scalar argRadians )
{
    Matrix3x3 e(3,3);
    Scalar c = std::cos( argRadians );
    Scalar s = std::sin( argRadians );
    e(0,0) =  c; e(0,1) =  0; e(0,2) = -s;
    e(1,0) =  0; e(1,1) =  1; e(1,2) =  0;
    e(2,0) =  s; e(2,1) =  0; e(2,2) =  c;
    return e;
}

/// Returns a 3x3 rotation matrix representing a rotation of argRadians
/// around the y-axis.
Matrix3x3 tau::rotZ( Scalar argRadians )
{
    Matrix3x3 e(3,3);
    Scalar c = std::cos( argRadians );
    Scalar s = std::sin( argRadians );
    e(0,0) =  c; e(0,1) =  s; e(0,2) =  0;
    e(1,0) = -s; e(1,1) =  c; e(1,2) =  0;
    e(2,0) =  0; e(2,1) =  0; e(2,2) =  1;
    return e;
}

/// Returns the rotation matrix representing a rotation of angle radians
/// around the axis.  Based on the Rodrigues' rotation formula.
Matrix3x3 tau::rotFromAxisAngle( const Vector3& aAxis, Scalar aRadians )
{
    // note that Eigen's rep is inverted
    Eigen::AngleAxis<Scalar> aa( -aRadians, aAxis );
    return aa.toRotationMatrix();
//    Vector3 axis = aAxis.normalized();
//    Scalar s = std::sin( aRadians );
//    Scalar c = std::cos( aRadians );
//    Matrix3x3 skew = skewSym(axis);
//    Matrix3x3 out = eye() + s*skew + (1-c)*(skew*skew);
//    return out.transpose();  // why is transposing needed?
}

Matrix3x3 tau::rotFromTwoVectors( const Vector3& aFrom, const Vector3& aTo )
{
    Vector3 axis = aFrom.cross( aTo );
    Scalar len = axis.norm();
    Scalar angle = atan2( len, aFrom.dot( aTo ) );
    const double eps = 1e-8;
    if( len > eps )
    {
        return rotFromAxisAngle( axis, angle );
    }
    else
    {
        // vectors are practically identical, so leave alone
        return eye();
    }
}

std::ostream& tau::operator<<( std::ostream& out, const SpatialVector& arg )
{
    out << arg.data_;
    return out;
}

std::ostream& tau::operator<<( std::ostream& out, const XForm& arg )
{
    out << "XForm\n\tE:\n" << arg.m_E << "\n\tr:\n" << arg.m_r;
    return out;
}

std::ostream& tau::operator<<( std::ostream& out, const SpatialInertia& arg )
{
    out << "SpatialInertia\n\tmass:\t" << arg.m_mass << "\n\tcom:" << arg.m_com
            << "\n\tI:\n" << arg.m_I << "\n";
    return out;
}

/// XForm composition, standard matrix multiplication.
XForm tau::operator*( const XForm& left, const XForm& right )
{
    using namespace tau;
    Matrix3x3 rot = left.m_E*right.m_E;
    Vector3 trans = right.m_r + (right.m_E.transpose() * left.m_r);
    return XForm( rot, trans );
}

SpatialMotionVector tau::operator*( Scalar aFactor, 
                                    const SpatialMotionVector& aVec )
{
    return SpatialMotionVector( aFactor * aVec.data_ );
}

/// Element-wise multiplication by scalar.
SpatialMotionVector tau::operator*( const SpatialMotionVector& aVec, 
                                    Scalar aFactor )
{
    return SpatialMotionVector( aFactor * aVec.data_ );
}

SpatialMotionVector tau::operator+( const SpatialMotionVector& a,
                                   const SpatialMotionVector& b )
{
    return SMV( a[0] + b[0],
                a[1] + b[1],
                a[2] + b[2],
                a[3] + b[3],
                a[4] + b[4],
                a[5] + b[5] );
}

SpatialForceVector tau::operator+( const SpatialForceVector& a,
                                   const SpatialForceVector& b )
{
    return SFV( a[0] + b[0],
                a[1] + b[1],
                a[2] + b[2],
                a[3] + b[3],
                a[4] + b[4],
                a[5] + b[5] );
}

SpatialForceVector tau::operator*( Scalar aFactor, 
                                   const SpatialForceVector& aVec )
{
    return SpatialForceVector( aFactor * aVec.data_ );
}
	
/// Element-wise multiplication by scalar.
SpatialForceVector tau::operator*( const SpatialForceVector& aVec, 
                                   Scalar aFactor )
{
    return SpatialForceVector( aFactor * aVec.data_ );
}


Vector6 tau::ltToVector( const Matrix3x3& m )
{
    //        return Vector6( m(0,0), m(1,0), m(1,1), m(2,0), m(2,1), m(2,2) );
    Vector6 out;
    out << m(0,0), m(1,0), m(1,1), m(2,0), m(2,1), m(2,2) ;
    return out;
}

/// Construct a symmetric 3x3 Matrix using the given elements, as:
/// v[0] v[1] v[3]
/// v[1] v[2] v[4]
/// v[3] v[4] v[5]
Matrix3x3 tau::ltFromVector( const Vector6& v )
{
    Matrix3x3 out;
    out << v[0], v[1], v[3],
    v[1], v[2], v[4],
    v[3], v[4], v[5];
    return out;
}


////////////////////////////////////////////////////////////////////////////////
/// Point


tau::Point
::Point()
: data_()
{
    data_.setZero();
}

tau::Point
::Point( Scalar aX, Scalar aY, Scalar aZ )
: data_( aX, aY, aZ )
{
    // Noop
}

Scalar 
tau::Point
::operator[]( int aIdx ) const
{
    return data_[aIdx];
}

Scalar& 
tau::Point
::operator[]( int aIdx )
{
    return data_[aIdx];
}

////////////////////////////////////////////////////////////////////////////////
/// SpatialInertia

tau::SpatialInertia
::SpatialInertia( )
: m_mass( 1.0 )
{
    m_com.setZero();
    m_I.setZero();
    m_I(0) = 1.0;
    m_I(2) = 1.0;
    m_I(5) = 1.0;
}

tau::SpatialInertia
::SpatialInertia( Scalar mass, const Vector3& com, const Vector6& inertia )
: m_mass( mass ),
  m_com( com ),
  m_I( inertia )
{
    // Noop
}

Matrix6x6
tau::SpatialInertia::toMatrix6x6() const
{
    Matrix6x6 out;
    Matrix3x3 cx = skewSym( m_com );
    Matrix3x3 mcx = m_mass * cx;
    Matrix3x3 cxT = - cx;
    Matrix3x3 mcxT = m_mass * cxT;

    out.corner<3,3>(Eigen::TopLeft) = inertiaMatrix() + ( mcx * cxT );
    out.corner<3,3>(Eigen::TopRight) = mcx;
    out.corner<3,3>(Eigen::BottomLeft) = mcxT;
    out.corner<3,3>(Eigen::BottomRight) = m_mass * Matrix3x3::Identity();
    return out;
}

Matrix3x3
tau::SpatialInertia
::inertiaMatrix() const
{
    /// m_I[0] m_I[1] m_I[3]
    /// m_I[1] m_I[2] m_I[4]
    /// m_I[3] m_I[4] m_I[5]
    Matrix3x3 out;
    out << m_I[0], m_I[1], m_I[3],
           m_I[1], m_I[2], m_I[4],
           m_I[3], m_I[4], m_I[5] ;
    return out;
}


SpatialForceVector tau::operator*( const SpatialInertia& I, const SpatialMotionVector& v )
{
    return SpatialForceVector( I.toMatrix6x6() * v.asVector6() );
}



