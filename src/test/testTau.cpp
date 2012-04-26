///
/// \file testTau.cpp
/// \brief Unit tests for the tau project.
/// Copyright 2010 Brian Allen
///

#include "tau.hpp"
#include "robot.hpp"
#include "TauRobot.hpp"
#include "OdeRobot.hpp"

#include <iostream>


using namespace tau;

/// Test the tau library
#define BOOST_TEST_MODULE TauTest


#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma clang ignored "-Wunused-variable"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>


/// Default percentage error tolerance for floating-point values.
const double tolPer = 1e-5;


// WARN (generates message) < CHECK < REQUIRE (stops execution)

// BOOST_REQUIRE_EQUAL( a, b );
// BOOST_FAIL( "comment" );
// BOOST_WARN( pred );
// BOOST_CHECK_MESSAGE( pred, msg );
// BOOST_CHECK_CLOSE( a, b, tolerancePercent )
// BOOST_CHECK_SMALL( a, tol )

/// Testing the tau library.
BOOST_AUTO_TEST_SUITE( tauTestSuite )

/// Testing base constructors and direct accessors. 
BOOST_AUTO_TEST_CASE( testConstructorsAndAccessors )
{
	Matrix3x3 eye3 = eye();
	Matrix3x3 zero3 = zero();
	BOOST_CHECK_CLOSE( eye3( 0,0 ), 1.0, tolPer );
	BOOST_CHECK_CLOSE( eye3( 0,1 ), 0.0, tolPer );
	BOOST_CHECK_CLOSE( zero3( 2,2 ), 0.0, tolPer );
    
    Point p( 1,2,3 );
    BOOST_CHECK_CLOSE( p[X], 1, tolPer );
    BOOST_CHECK_CLOSE( p[Y], 2, tolPer );
    BOOST_CHECK_CLOSE( p[Z], 3, tolPer );
    
    Point p2( 10,10,10 );
    Vector3 vec = p2 - p;
    BOOST_CHECK_CLOSE( vec[X], 9, tolPer );
    BOOST_CHECK_CLOSE( vec[Y], 8, tolPer );
    BOOST_CHECK_CLOSE( vec[Z], 7, tolPer );
    
    Matrix3x3 rZ = rotZ( 0.5 );
    Vector3 zVec = Vector3::UnitZ();
    Matrix3x3 rZalso = rotFromAxisAngle( zVec, 0.5 );
    BOOST_CHECK_CLOSE( rZ(0,0), rZalso(0,0), tolPer );
    BOOST_CHECK_CLOSE( rZ(1,0), rZalso(1,0), tolPer );
    BOOST_CHECK_CLOSE( rZ(2,0), rZalso(2,0), tolPer );
    BOOST_CHECK_CLOSE( rZ(0,1), rZalso(0,1), tolPer );
    BOOST_CHECK_CLOSE( rZ(1,1), rZalso(1,1), tolPer );
    BOOST_CHECK_CLOSE( rZ(2,1), rZalso(2,1), tolPer );
    BOOST_CHECK_CLOSE( rZ(0,2), rZalso(0,2), tolPer );
    BOOST_CHECK_CLOSE( rZ(1,2), rZalso(1,2), tolPer );
    BOOST_CHECK_CLOSE( rZ(2,2), rZalso(2,2), tolPer );

    double x = 1; double y = 2; double z = 3;
    XForm transX = XForm::fromTranslation( Vector3( x, y, z ) );

}

/// Tests based on problems from Featherstone's 2008 handouts.
BOOST_AUTO_TEST_CASE( testProblemsB1 )
{
	SMV hinge1;
	hinge1.setZero();
	hinge1[Z] = 1;  // rotation around the z-axis

	SMV hinge2_joint2;
	hinge2_joint2.setZero();
	hinge2_joint2[Z] = 1;  // rotation around the z-axis
	
	// now, move hinge2 from the joint position to the world position
	Point jointPos( 0,0,1 );
	Point originPos( 0,0,0 );
	// move from the joint at (0,0,1) to origin at (0,0,0)
	Vector3 r = (originPos - jointPos);
	// constructor plucker transform from this motion (no rotation)
	XForm jointToOrigin = XForm::fromTranslation( r );
	SMV hinge2_origin = jointToOrigin.apply( hinge2_joint2 );
	
}

BOOST_AUTO_TEST_CASE( testForwardKinematics )
{
    
}


BOOST_AUTO_TEST_CASE( testCreatingOneLinkRevoluteJointRobot )
{
    Robot robot;
    TauBody body0( &robot );
    BOOST_CHECK_EQUAL( 0, robot.bodyIndex( &body0 ) );
	TauBody body1( &robot );
    BOOST_CHECK_EQUAL( 1, robot.bodyIndex( &body1 ) );
    //TODO set masses
	
	Vector3 anchor1( 1,0,0 );  // in local
	Vector3 axis1( 0,0,1 );  // in local
    
    // attach the bodies with a joint.  should set the parent-child relations
	TauRevoluteJoint joint1( &body0, &body1, anchor1, axis1 );
    BOOST_CHECK_EQUAL( &body0, body1.parent() );  // parentage assigned in joint attach/ctor
    BOOST_CHECK( body0.isBase() );
    BOOST_CHECK_EQUAL( static_cast<TauBody*>(NULL), body0.parent() ); // parent of zeroth body should be null
    BOOST_CHECK_EQUAL( 0, robot.bodyIndex( body1.parent() ) ); // parent of body 1 should be root
    BOOST_CHECK_EQUAL( &body1, joint1.body() ); // body of joint 1 is body 1
    
    // Now that the joint has been attached, we can check the positions
    // of the bodies as the joints are rotated.

    // Set state
    joint1.q( 0, 0 ); // default position, no change from starting position
    joint1.dq( 0, 0 ); joint1.ddq( 0, 0 ); // not needed for now
    
    {
        // check that joint xform is identity when q == 0
        XForm jointXForm = joint1.xform();        
        BOOST_CHECK_EQUAL( jointXForm.r(), Vector3::Zero() );
        BOOST_CHECK_EQUAL( jointXForm.E(), Matrix3x3::Identity() );

        XForm joint_i_treeXForm = joint1.treeXForm();
        std::cerr << "Joint1 Tree XForm:\n" << joint_i_treeXForm << "\n\n";
        BOOST_CHECK_EQUAL( joint_i_treeXForm.E(), Matrix3x3::Identity() );
        BOOST_CHECK_EQUAL( joint_i_treeXForm.r()[0], 1 );
        BOOST_CHECK_EQUAL( joint_i_treeXForm.r()[1], 0 );
        BOOST_CHECK_EQUAL( joint_i_treeXForm.r()[2], 0 );
    }
    robot.solveKinematics();
    
    // position in world only valid after solveKinematics
    int body0Index = robot.bodyIndex( &body0 );
    {
        BOOST_CHECK_EQUAL( body0Index, 0 ); // this is the zero'th body
        XForm body0_from_base = robot.xForm_body_from_base( body0Index );
        Vector3 r = body0_from_base.r();
        BOOST_CHECK_CLOSE( r[0], 0, tolPer );
        BOOST_CHECK_CLOSE( r[1], 0, tolPer );
        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
    }
    {
        XForm body1_from_base = robot.xForm_body_from_base( robot.bodyIndex( &body1 ) );
        Vector3 r = body1_from_base.r();
        BOOST_CHECK_CLOSE( r[0], 1, tolPer );
        BOOST_CHECK_CLOSE( r[1], 0, tolPer );
        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
    }
    {
        joint1.q( 0, TAU_PI / 2. );
        robot.solveKinematics();
        XForm body1_from_base = robot.xForm_body_from_base( robot.bodyIndex( &body1 ) );
        Vector3 r = body1_from_base.r();
        BOOST_CHECK_CLOSE( r[0], 1, tolPer );
        BOOST_CHECK_CLOSE( r[1], 0, tolPer );
        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
    }
}


BOOST_AUTO_TEST_CASE( testCreatingTwoLinkRevoluteJointRobot )
{
    Robot robot;
    TauBody body0( &robot );
    BOOST_CHECK_EQUAL( 0, robot.bodyIndex( &body0 ) );
	TauBody body1( &robot );
    BOOST_CHECK_EQUAL( 1, robot.bodyIndex( &body1 ) );
	TauBody body2( &robot );
    BOOST_CHECK_EQUAL( 2, robot.bodyIndex( &body2 ) );

	Vector3 anchor1( 1,0,0 );  // in local
	Vector3 axis1( 0,0,1 );  // in local
    
    // attach the bodies with a joint.  should set the parent-child relations
	TauRevoluteJoint joint1( &body0, &body1, anchor1, axis1 );
	TauRevoluteJoint joint2( &body1, &body2, anchor1, axis1 );
    
    joint1.q( 0, 0 );
    joint2.q( 0, 0 );
    robot.solveKinematics();
    {
        XForm body2_from_base = robot.xForm_body_from_base( robot.bodyIndex( &body2 ) );
        Vector3 r = body2_from_base.r();
        BOOST_CHECK_CLOSE( r[0], 2, tolPer );
        BOOST_CHECK_CLOSE( r[1], 0, tolPer );
        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
    }
    
    joint1.q( 0, TAU_PI / 2.0 );
    joint2.q( 0, 0 );
    robot.solveKinematics();
    {
        XForm body2_from_base = robot.xForm_body_from_base( robot.bodyIndex( &body2 ) );
        Vector3 r = body2_from_base.r();
        BOOST_CHECK_CLOSE( r[0], 1, tolPer );
        BOOST_CHECK_CLOSE( r[1], 1, tolPer );
        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
    }    
}

BOOST_AUTO_TEST_CASE( testKinematics )
{
    Robot robot;
    TauBody body0( &robot );
    BOOST_CHECK_EQUAL( 0, robot.bodyIndex( &body0 ) );
	TauBody body1( &robot );
    BOOST_CHECK_EQUAL( 1, robot.bodyIndex( &body1 ) );
	TauBody body2( &robot );
    BOOST_CHECK_EQUAL( 2, robot.bodyIndex( &body2 ) );
 	TauBody body3( &robot );
    BOOST_CHECK_EQUAL( 3, robot.bodyIndex( &body3 ) );
    
	Vector3 anchor1( 1,0,0 );  // in local
	Vector3 axis1( 0,0,1 );  // in local
    
    // attach the bodies with a joint.  should set the parent-child relations
	TauRevoluteJoint joint1( &body0, &body1, anchor1, axis1 );
	TauRevoluteJoint joint2( &body1, &body2, anchor1, axis1 );
	TauRevoluteJoint joint3( &body2, &body3, anchor1, axis1 );
    
    BOOST_CHECK( body0.isBase() );
    BOOST_CHECK( ! body1.isBase() );
    BOOST_CHECK( ! body2.isBase() );
    BOOST_CHECK( ! body3.isBase() );
    
    joint1.q( 0, 0 );
    joint2.q( 0, TAU_PI/2. );
    joint3.q( 0, -TAU_PI/2. );
    robot.solveKinematics();
    {
        XForm body3_from_base = robot.xForm_body_from_base( robot.bodyIndex( &body3 ) );
        Vector3 r = body3_from_base.r();
        BOOST_CHECK_CLOSE( r[0], 2, tolPer );
        BOOST_CHECK_CLOSE( r[1], 1, tolPer );
        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
    }
}


BOOST_AUTO_TEST_CASE( testKinematicsWithVelocity )
{
    Robot robot;
    TauBody body0( &robot );
    BOOST_CHECK_EQUAL( 0, robot.bodyIndex( &body0 ) );
	TauBody body1( &robot );
    BOOST_CHECK_EQUAL( 1, robot.bodyIndex( &body1 ) );

	Vector3 anchor1( 1,0,0 );  // in local
	Vector3 axis1( 0,0,1 );  // in local
    
    // attach the bodies with a joint.  should set the parent-child relations
	TauRevoluteJoint joint1( &body0, &body1, anchor1, axis1 );
	
    joint1.q( 0, 0 );          
    joint1.dq( 0, 0.1 ); // radians per sec
    
    robot.solveKinematics();
//    XForm body1_from_base = robot.xForm_body_from_base( robot.bodyIndex( &body1 ) );
//    {
//        Vector3 r = body3_from_base.r();
//        BOOST_CHECK_CLOSE( r[0], 1, tolPer );
//        BOOST_CHECK_CLOSE( r[1], 0, tolPer );
//        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
//    }
//    {
//        Vector3 r = body3_from_base.r();
//        BOOST_CHECK_CLOSE( r[0], 2, tolPer );
//        BOOST_CHECK_CLOSE( r[1], 1, tolPer );
//        BOOST_CHECK_CLOSE( r[2], 0, tolPer );
//    }
}


/// Test that translation won't affect linear velocity.
BOOST_AUTO_TEST_CASE( testPluckerTranslateDoesntChangeLinearVel )
{
    double x = 1; double y = 2; double z = 3;
    double a = 4; double b = 5; double c = 6;
    SpatialMotionVector m( 0,0,0, x,y,z );
    XForm transX = XForm::fromTranslation( Vector3( a, b, c ) );
    SpatialMotionVector mp = transX.apply( m );
    BOOST_CHECK_CLOSE( mp[0],  0.0, tolPer );
    BOOST_CHECK_CLOSE( mp[1],  0.0, tolPer );
    BOOST_CHECK_CLOSE( mp[2],  0.0, tolPer );
    BOOST_CHECK_CLOSE( mp[3],    x, tolPer );
    BOOST_CHECK_CLOSE( mp[4],    y, tolPer );
    BOOST_CHECK_CLOSE( mp[5],    z, tolPer );
}

/// Testing general translation transformation on motion vectors.
BOOST_AUTO_TEST_CASE( testPluckerTranslate )
{
    double wx = 1; double wy = 2; double wz = 3;
    double vx = 4; double vy = 5; double vz = 6;
    double x  = 7; double y  = 8; double z  = 9;
    SpatialMotionVector m( wx,wy,wz, vx,vy,vz );
    XForm transX = XForm::fromTranslation( Vector3( x,y,z ) );
    SpatialMotionVector mp = transX.apply( m );
    BOOST_CHECK_CLOSE( mp[0], wx, tolPer );
    BOOST_CHECK_CLOSE( mp[1], wy, tolPer );
    BOOST_CHECK_CLOSE( mp[2], wz, tolPer );
    BOOST_CHECK_CLOSE( mp[3], vx + z*wy - y*wz, tolPer );
    BOOST_CHECK_CLOSE( mp[4], vy - z*wx + x*wz, tolPer );
    BOOST_CHECK_CLOSE( mp[5], vz + y*wx - x*wy, tolPer );
}

/// Testing general translation transformation on force vectors.
BOOST_AUTO_TEST_CASE( testPluckerTranslateForce )
{
    double wx = 1; double wy = 2; double wz = 3;
    double vx = 4; double vy = 5; double vz = 6;
    double x  = 7; double y  = 8; double z  = 9;
    SpatialForceVector f( wx,wy,wz, vx,vy,vz );
    XForm transX = XForm::fromTranslation( Vector3( x,y,z ) );
    SpatialForceVector fp = transX.apply( f );
    
    SpatialForceVector expected( wx + z*vy - y*vz,
                                 wy - z*vx + x*vz,
                                 wz + y*vx - x*vy,
                                 vx,
                                 vy,
                                 vz );
    //std::cerr << "Translated force vector: \n" << fp.data() << "\n\tExpected: \n" << expected.data() << "\n";
    
    
    // Checking near-zero values is troublesome with CLOSE
   
	double absTol = 1e-7;
	BOOST_CHECK( std::abs( fp[0] - (wx + z*vy - y*vz) ) < absTol );
	//BOOST_CHECK_CLOSE( fp[0], wx + z*vy - y*vz, tolPer );
    
	BOOST_CHECK( std::abs( fp[1] - (wy - z*vx + x*vz) ) < absTol );
	//BOOST_CHECK_CLOSE( fp[1], wy - z*vx + x*vz, tolPer );
    
	BOOST_CHECK( std::abs( fp[2] - (wz + y*vx - x*vy) ) < absTol );
	//BOOST_CHECK_CLOSE( fp[2], wz + y*vx - x*vy, tolPer );
    
	BOOST_CHECK_CLOSE( fp[3], vx, tolPer );
    BOOST_CHECK_CLOSE( fp[4], vy, tolPer );
    BOOST_CHECK_CLOSE( fp[5], vz, tolPer );
}

/// Test conversions to other formats.
BOOST_AUTO_TEST_CASE( testConversions )
{
	SpatialMotionVector x( 1,2,3, 4,5,6 );
	double raw[3];
	x.copyAngularToArray( raw );
	BOOST_CHECK_EQUAL( raw[0], 1 );
	BOOST_CHECK_EQUAL( raw[1], 2 );
	BOOST_CHECK_EQUAL( raw[2], 3 );
	x.copyLinearToArray( raw );
	BOOST_CHECK_EQUAL( raw[0], 4 );
	BOOST_CHECK_EQUAL( raw[1], 5 );
	BOOST_CHECK_EQUAL( raw[2], 6 );	
}

/// Detailed test of the cross product matrix (aka skew-symmetric operator)
BOOST_AUTO_TEST_CASE( testMotionCrossProductMatrix )
{
	using namespace tau;
	
	Vector3 omega( 1, 2, 3 );
	Vector3 vel( 4, 5, 6 );
	SMV s( omega, vel );
	Matrix6x6 sx = s.skewSym();
    BOOST_CHECK_CLOSE( sx(0,0),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(0,1), -3, tolPer );
	BOOST_CHECK_CLOSE( sx(0,2),  2, tolPer );

	BOOST_CHECK_CLOSE( sx(0,3),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(0,4),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(0,5),  0, tolPer );

	BOOST_CHECK_CLOSE( sx(1,0),  3, tolPer );
	BOOST_CHECK_CLOSE( sx(1,1),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(1,2), -1, tolPer );
	
	BOOST_CHECK_CLOSE( sx(1,3),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(1,4),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(1,5),  0, tolPer );

	BOOST_CHECK_CLOSE( sx(2,0), -2, tolPer );
	BOOST_CHECK_CLOSE( sx(2,1),  1, tolPer );
	BOOST_CHECK_CLOSE( sx(2,2),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(2,3),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(2,4),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(2,5),  0, tolPer );

	BOOST_CHECK_CLOSE( sx(3,0),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(3,1), -6, tolPer );
	BOOST_CHECK_CLOSE( sx(3,2),  5, tolPer );
	
	BOOST_CHECK_CLOSE( sx(3,3),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(3,4), -3, tolPer );
	BOOST_CHECK_CLOSE( sx(3,5),  2, tolPer );

	BOOST_CHECK_CLOSE( sx(4,0),  6, tolPer );
	BOOST_CHECK_CLOSE( sx(4,1),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(4,2), -4, tolPer );
	
	BOOST_CHECK_CLOSE( sx(4,3),  3, tolPer );
	BOOST_CHECK_CLOSE( sx(4,4),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(4,5), -1, tolPer );

	BOOST_CHECK_CLOSE( sx(5,0), -5, tolPer );
	BOOST_CHECK_CLOSE( sx(5,1),  4, tolPer );
	BOOST_CHECK_CLOSE( sx(5,2),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(5,3), -2, tolPer );
	BOOST_CHECK_CLOSE( sx(5,4),  1, tolPer );
	BOOST_CHECK_CLOSE( sx(5,5),  0, tolPer );
}

/// Detailed test of the cross product matrix (aka skew-symmetric operator)
BOOST_AUTO_TEST_CASE( testForceCrossProductMatrix )
{
	using namespace std;
	using namespace tau;
	
	Vector3 t( 1, 2, 3 );
	Vector3 f( 4, 5, 6 );
	SFV sfv( t, f );
	Matrix6x6 sx = sfv.skewSym();
    BOOST_CHECK_CLOSE( sx(0,0),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(0,1), -3, tolPer );
	BOOST_CHECK_CLOSE( sx(0,2),  2, tolPer );
	
	BOOST_CHECK_CLOSE( sx(0,3),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(0,4), -6, tolPer );
	BOOST_CHECK_CLOSE( sx(0,5),  5, tolPer );
	
	BOOST_CHECK_CLOSE( sx(1,0),  3, tolPer );
	BOOST_CHECK_CLOSE( sx(1,1),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(1,2), -1, tolPer );
	
	BOOST_CHECK_CLOSE( sx(1,3),  6, tolPer );
	BOOST_CHECK_CLOSE( sx(1,4),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(1,5), -4, tolPer );
	
	BOOST_CHECK_CLOSE( sx(2,0), -2, tolPer );
	BOOST_CHECK_CLOSE( sx(2,1),  1, tolPer );
	BOOST_CHECK_CLOSE( sx(2,2),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(2,3), -5, tolPer );
	BOOST_CHECK_CLOSE( sx(2,4),  4, tolPer );
	BOOST_CHECK_CLOSE( sx(2,5),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(3,0),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(3,1),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(3,2),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(3,3),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(3,4), -3, tolPer );
	BOOST_CHECK_CLOSE( sx(3,5),  2, tolPer );
	
	BOOST_CHECK_CLOSE( sx(4,0),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(4,1),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(4,2),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(4,3),  3, tolPer );
	BOOST_CHECK_CLOSE( sx(4,4),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(4,5), -1, tolPer );

	BOOST_CHECK_CLOSE( sx(5,0),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(5,1),  0, tolPer );
	BOOST_CHECK_CLOSE( sx(5,2),  0, tolPer );
	
	BOOST_CHECK_CLOSE( sx(5,3), -2, tolPer );
	BOOST_CHECK_CLOSE( sx(5,4),  1, tolPer );
	BOOST_CHECK_CLOSE( sx(5,5),  0, tolPer );

	Vector3 omega( 1, 2, 3 );
	Vector3 v( 4, 5, 6 );
	SMV smv( omega, v );
	Matrix6x6 smvx = smv.skewSym();
	
	for( int i = 0; i < 6; ++i )
	{
		for( int j = 0; j < 6; ++j )
		{
			BOOST_CHECK_CLOSE( sx(i,j), (-smvx.transpose())(i,j), tolPer );
		}
	}
}

BOOST_AUTO_TEST_CASE( testXFormMultiply )
{
    using namespace tau;
    
    Vector3 t = Vector3( 1,2,3 );
    XForm trans = XForm::fromTranslation( t );
    
    Vector3 axis = Vector3(0,1,1);
    Scalar angle = M_PI/4.0;
    Matrix3x3 r = rotFromAxisAngle( axis, angle );
    XForm rot = XForm::fromRotationMatrix( r );
    
    XForm a = rot * trans;
    XForm b( r, t );
    
    BOOST_REQUIRE_EQUAL( a, b );
}

#include "testOdeRobot.hpp"


/// Test conversions to other formats.
BOOST_AUTO_TEST_CASE( testSpatialInertia )
{
    // Inertia properties for a sphere, mass=1, radius=0.5, one unit away from the axis
    Vector3 com;
    com << 1,
           0,
           0;
    Matrix3x3 rotationalInertiaAboutCOM;
    rotationalInertiaAboutCOM << 0.1,   0,   0,
                                   0, 0.1,   0,
                                   0,   0, 0.1;
    Vector6 lowerTriangleInertia = ltToVector( rotationalInertiaAboutCOM );
    Scalar mass = 1.0;
    SpatialInertia I( mass, com, lowerTriangleInertia );
    Matrix6x6 SI = I.toMatrix6x6();
    BOOST_CHECK_CLOSE( SI(0,0), 0.1, tolPer );
    BOOST_CHECK_CLOSE( SI(1,1), 1.1, tolPer );
    BOOST_CHECK_CLOSE( SI(2,2), 1.1, tolPer );
    BOOST_CHECK_CLOSE( SI(3,3), 1, tolPer );
    BOOST_CHECK_CLOSE( SI(4,4), 1, tolPer );
    BOOST_CHECK_CLOSE( SI(5,5), 1, tolPer );

    BOOST_CHECK_CLOSE( SI(1,5), -1, tolPer );
    BOOST_CHECK_CLOSE( SI(2,4),  1, tolPer );

    BOOST_CHECK_CLOSE( SI(4,2),  1, tolPer );
    BOOST_CHECK_CLOSE( SI(5,1), -1, tolPer );

    // check that it's symmetric
    for( size_t r=0; r<6; ++r )
    {
        for( size_t c=0; c<6; ++c )
        {
            BOOST_CHECK_CLOSE( SI(r,c), SI(c,r), tolPer );
        }
    }

    SpatialMotionVector a( 0,0,5, 0,0,0 );

    SFV f = I * a;

    BOOST_CHECK_CLOSE( f[0], 0.0, tolPer );
    BOOST_CHECK_CLOSE( f[1], 0.0, tolPer );
    BOOST_CHECK_CLOSE( f[2], 5.5, tolPer );
    BOOST_CHECK_CLOSE( f[3], 0.0, tolPer );
    BOOST_CHECK_CLOSE( f[4], 5.0, tolPer );
    BOOST_CHECK_CLOSE( f[5], 0.0, tolPer );
}


/// End tests for the tau library.
BOOST_AUTO_TEST_SUITE_END()

