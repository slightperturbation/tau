//
//  testOdeRobot.hpp
//  tau
//
//  Copyright 2010 Brian Allen. All rights reserved.
//

#include "OdeRobot.hpp"
#include <ode/ode.h>

/// Default percentage error tolerance for floating-point values.
const double tolPer = 1e-5;

class OneBodyOdeTestHarness
{
public:
    dWorldID world;
    dSpaceID space;
    dBodyID body0; // fixed by joint 0
    dBodyID body1; // moved by joint 1
    dJointID joint0; // grounding joint, holding body0 fixed; **no analogue in Robot**
    dJointID joint1; // controls body1
    tau::OdeRobot* robot;
    double dt;

    OneBodyOdeTestHarness( void )
    : robot( NULL ), dt( 0.01 )
    {
        dInitODE();
        world = dWorldCreate();
        space = 0; //dHashSpaceCreate();
        //dWorldSetGravity( space, 0, 0, -9.8 );

        buildRobot();
    }

    ~OneBodyOdeTestHarness()
    {
        delete robot;
        if( space )
        {
            dSpaceDestroy( space );
            space = 0;
        }
        if( world )
        {
            dWorldDestroy( world );
            world = 0;
        }
        dCloseODE();
    }

    void buildRobot( void )
    {
        // create a mass centered on the body's coordinate frame
        dMass mass;
        dMassSetSphereTotal( &mass, 1.0 /* total mass */, 0.5 /* radius */ );

        // fixed body
        body0 = dBodyCreate( world );
        body1 = dBodyCreate( world );
        dBodySetMass( body0, &mass );
        dBodySetMass( body1, &mass );
        dBodySetPosition( body0, 0, 0, 0 );
        dBodySetPosition( body1, 1, 0, 0 );

        // fix the rootBody to the world, (ie, fixed base robot)
        joint0 = dJointCreateFixed( world, 0 );
        dJointAttach( joint0, 0, body0 );
        dJointSetFixed( joint0 );

        joint1 = dJointCreateHinge( world, 0 );
        dJointAttach( joint1, body0, body1 );
        dJointSetHingeAnchor( joint1, 0, 0, 0 );
        dJointSetHingeAxis( joint1, 0, 0, 1 );

        robot = new tau::OdeRobot( body0 );
    }

    // set initial velocity on joint with an impulse
    void applyImpulseToArm( double newton_meter_seconds )
    {
        double strength = newton_meter_seconds * dt;
        dJointAddHingeTorque( joint1, strength );
    }

    void forwardSim( double seconds )
    {
        // advance seconds
        int steps = (1.0/dt) * seconds;
        for( int i = 0; i < steps; ++i )
        {
            dWorldStep( world, dt );
            double q =  dJointGetHingeAngle( joint1 );
            double dq = dJointGetHingeAngleRate( joint1 );
//            std::cerr << q << "\t\t" << dq << "\n";
        }
    }
    double dq( void ) const
    {
        return dJointGetHingeAngleRate( joint1 );
    }
};



class TreeRobotOdeTestHarness
{
public:
    dWorldID world;
    dSpaceID space;
    dBodyID body0; // fixed by joint 0
    dBodyID body1; // moved by joint 1
    dBodyID body2; // moved by joint 2
    dJointID joint0; // grounding joint, holding body0 fixed; **no analogue in Robot**
    dJointID joint1; // controls body1 (anchored to body0)
    dJointID joint2; // controls body2 (anchored to body0)
    tau::OdeRobot* robot;
    double dt;

    TreeRobotOdeTestHarness( void )
    : robot( NULL ), dt( 0.01 )
    {
        dInitODE();
        world = dWorldCreate();
        space = 0; //dHashSpaceCreate();
        //dWorldSetGravity( space, 0, 0, -9.8 );

        buildRobot();
    }

    ~TreeRobotOdeTestHarness()
    {
        delete robot;
        if( space )
        {
            dSpaceDestroy( space );
            space = 0;
        }
        if( world )
        {
            dWorldDestroy( world );
            world = 0;
        }
        dCloseODE();
    }

    void buildRobot( void )
    {
        // create a mass centered on the body's coordinate frame
        dMass mass;
        dMassSetSphereTotal( &mass, 1.0 /* density */, 0.5 /* radius */ );

        // fixed body
        body0 = dBodyCreate( world );
        body1 = dBodyCreate( world );
        body2 = dBodyCreate( world );
        dBodySetMass( body0, &mass );
        dBodySetMass( body1, &mass );
        dBodySetMass( body2, &mass );
        dBodySetPosition( body0, 0, 0, 0 );
        dBodySetPosition( body1, 1, 0, 0 );
        dBodySetPosition( body2, 0, 1, 0 );

        // fix the rootBody to the world, (ie, fixed base robot)
        joint0 = dJointCreateFixed( world, 0 );
        dJointAttach( joint0, 0, body0 );
        dJointSetFixed( joint0 );

        joint2 = dJointCreateHinge( world, 0 );
        dJointAttach( joint2, body0, body2 );
        dJointSetHingeAnchor( joint2, 0, 0.5, 0 );
        dJointSetHingeAxis( joint2, 0, 0, 1 );

        joint1 = dJointCreateHinge( world, 0 );
        dJointAttach( joint1, body0, body1 );
        dJointSetHingeAnchor( joint1, 0.5, 0, 0 );
        dJointSetHingeAxis( joint1, 0, 0, 1 );

        robot = new tau::OdeRobot( body0 );
    }

    // set initial velocity on joint with an impulse
    void applyImpulseToArm( double newton_meter_seconds )
    {
        double strength = newton_meter_seconds * dt;
        dJointAddHingeTorque( joint1, strength );
    }

    void forwardSim( double seconds )
    {
        // advance seconds
        int steps = (1.0/dt) * seconds;
        for( int i = 0; i < steps; ++i )
        {
            dWorldStep( world, dt );
            double q =  dJointGetHingeAngle( joint1 );
            double dq = dJointGetHingeAngleRate( joint1 );
//            std::cerr << q << "\t\t" << dq << "\n";
        }
    }
    double dq( void ) const
    {
        return dJointGetHingeAngleRate( joint1 );
    }
};


class OdeTestHarness
{
public:
    dWorldID world;
    dSpaceID space;
    dBodyID body0;
    dBodyID body1;
    dBodyID body2;
    dJointID joint0; // grounding joint, holding body0 fixed; **no analogue in Robot**
    dJointID joint1; // controls body1
    dJointID joint2; // controls body2
    tau::OdeRobot* robot;
    double dt;
    
    OdeTestHarness( void )
    : robot( NULL ), dt( 0.01 )
    {
        dInitODE();
        world = dWorldCreate();
        space = 0; //dHashSpaceCreate();
        //dWorldSetGravity( space, 0, 0, -9.8 );
        
        buildRobot();
    }
    
    ~OdeTestHarness()
    {
        delete robot;
        if( space ) 
        {
            dSpaceDestroy( space );
            space = 0;
        }
        if( world )
        {
            dWorldDestroy( world );
            world = 0;
        }
        dCloseODE();
    }
    
    void buildRobot( void )
    {
        // create a mass centered on the body's coordinate frame
        dMass mass;
        dMassSetSphereTotal( &mass, 1.0 /* total mass */, 0.5 /* radius */ );

        // fixed body 
        body0 = dBodyCreate( world );
        body1 = dBodyCreate( world );
        body2 = dBodyCreate( world );
        dBodySetMass( body0, &mass );
        dBodySetMass( body1, &mass );
        dBodySetMass( body2, &mass );
        dBodySetPosition( body0, 1, 0, 0 );
        dBodySetPosition( body1, 3, 0, 0 );
        dBodySetPosition( body2, 5, 0, 0 );
        
        // fix the rootBody to the world, (ie, fixed base robot)
        joint0 = dJointCreateFixed( world, 0 );
        dJointAttach( joint0, 0, body0 );
        dJointSetFixed( joint0 );
        
        joint1 = dJointCreateHinge( world, 0 );
        dJointAttach( joint1, body0, body1 );
        dJointSetHingeAnchor( joint1, 2, 0, 0 );
        dJointSetHingeAxis( joint1, 0, 0, 1 );

        joint2 = dJointCreateHinge( world, 0 );
        dJointAttach( joint2, body1, body2 );
        dJointSetHingeAnchor( joint2, 4, 0, 0 );
        dJointSetHingeAxis( joint2, 0, 0, 1 );

        robot = new tau::OdeRobot( body0 );
        
    }

    // set initial velocity on joint with an impulse
    void applyImpulseToArm( double newton_meter_seconds )
    {
        double strength = newton_meter_seconds * dt;
        dJointAddHingeTorque( joint1, strength );
    }

    void forwardSim( double seconds )
    {
        // advance seconds
        int steps = (1.0/dt) * seconds;
        for( int i = 0; i < steps; ++i )
        {
            dWorldStep( world, dt );
            double q =  dJointGetHingeAngle( joint1 );
            double dq = dJointGetHingeAngleRate( joint1 );
//            std::cerr << q << "\t\t" << dq << "\n";
        }
    }
    double dq( void ) const
    {
        return dJointGetHingeAngleRate( joint1 );
    }
};

BOOST_AUTO_TEST_CASE( testOdeRobot )
{
    OdeTestHarness ode;
    OdeRobot* robot = ode.robot;
    BOOST_REQUIRE( robot );
    BOOST_REQUIRE( robot->body( 0 ) );
    BOOST_REQUIRE( robot->body( 1 ) );
    BOOST_REQUIRE( robot->body( 2 ) );
    Joint* joint0 = robot->joint( 0 );
    BOOST_REQUIRE( joint0 == NULL );
    BOOST_REQUIRE( robot->joint( 1 ) );
    BOOST_REQUIRE( robot->joint( 2 ) );

    // check joint parentage is correct
    BOOST_CHECK_EQUAL( robot->body(1)->parent(), robot->body(1)->joint()->body() );
    BOOST_CHECK_EQUAL( robot->body(2)->parent(), robot->body(2)->joint()->body() );

    ode.applyImpulseToArm( 1.0 );
    ode.forwardSim( 1.0 );
}

BOOST_AUTO_TEST_CASE( testOneBodyConstruction )
{
    OneBodyOdeTestHarness ode;
    OdeRobot* robot = ode.robot;
    BOOST_REQUIRE( robot );
    BOOST_REQUIRE( robot->body( 0 ) ); // fixed, root body
    BOOST_REQUIRE( robot->body( 1 ) ); // moving, initially at 1,0,0
    BOOST_REQUIRE_EQUAL( robot->joint( 0 ), static_cast< Joint* >( NULL ) );
    OdeJoint* joint1 = dynamic_cast< OdeJoint* >( robot->joint( 1 ) );
    BOOST_REQUIRE( joint1 );
    BOOST_REQUIRE_EQUAL( joint1->getOdeJointID(), ode.joint1 );
    OdeBody* body0 = dynamic_cast< OdeBody* >( robot->body( 0 ) );
    BOOST_REQUIRE_EQUAL( body0->getOdeBodyID(), ode.body0 );
    OdeBody* body1 = dynamic_cast< OdeBody* >( robot->body( 1 ) );
    BOOST_REQUIRE_EQUAL( body1->getOdeBodyID(), ode.body1 );

    // check joint parentage is correct
    BOOST_CHECK_EQUAL( robot->body(1)->parent(), robot->body(1)->joint()->body() );
}

BOOST_AUTO_TEST_CASE( testTreeRobotOdeTestHarness )
{
    TreeRobotOdeTestHarness ode;
    OdeRobot* robot = ode.robot;
    BOOST_CHECK( robot );
    BOOST_CHECK( robot->body( 0 ) ); // fixed, root body
    BOOST_CHECK( robot->body( 1 ) ); // moving, initially at 1,0,0
    BOOST_CHECK( robot->body( 2 ) ); // moving, initially at 0,1,0
    BOOST_CHECK_EQUAL( robot->joint( 0 ), static_cast< Joint* >( NULL ) );

    // The checks below are very fragile, since ODE can reorder the joints
    OdeJoint* joint1 = dynamic_cast< OdeJoint* >( robot->joint( 1 ) );
    BOOST_CHECK( joint1 );
    BOOST_CHECK_EQUAL( joint1->getOdeJointID(), ode.joint1 );

    OdeJoint* joint2 = dynamic_cast< OdeJoint* >( robot->joint( 2 ) );
    BOOST_CHECK( joint2 );
    BOOST_CHECK_EQUAL( joint2->getOdeJointID(), ode.joint2 );

    OdeBody* body0 = dynamic_cast< OdeBody* >( robot->body( 0 ) );
    BOOST_CHECK_EQUAL( body0->getOdeBodyID(), ode.body0 );

    OdeBody* body1 = dynamic_cast< OdeBody* >( robot->body( 1 ) );
    BOOST_CHECK_EQUAL( body1->getOdeBodyID(), ode.body1 );

    OdeBody* body2 = dynamic_cast< OdeBody* >( robot->body( 2 ) );
    BOOST_CHECK_EQUAL( body2->getOdeBodyID(), ode.body2 );

    // check joint parentage is correct
    BOOST_CHECK_EQUAL( robot->body(1)->parent(), robot->body(1)->joint()->body() );
    BOOST_CHECK_EQUAL( robot->body(2)->parent(), robot->body(2)->joint()->body() );

}
BOOST_AUTO_TEST_CASE( testOneBodyInverseDynamics )
{
    OneBodyOdeTestHarness ode;

    VectorN ddq(1);
    ddq << 5;
    ode.robot->solveInverseDynamics( ddq, 1 );

    Joint* joint = ode.robot->joint(1);
    BOOST_REQUIRE( joint );

    VectorN torq = joint->getComputedTorque();
    BOOST_CHECK_CLOSE( torq(0), 5.5, tolPer );
}

BOOST_AUTO_TEST_CASE( testDistalInverseDynamics )
{
    OdeTestHarness ode;

    VectorN ddq(2);
    ddq << 0, 5;
    ode.robot->solveInverseDynamics( ddq );
    
    // acclerating a m=1, r=0.5 sphere around (0,0,1)
    // sphere I_xx = 2/5 * m * r^2, around center
    // I_xx = 2/5 * 1 * 0.25 = 2/5 * 1/4 = 2/20 = 1/10
    // parallel axis theorem
    // I_j = 1/10 + m * d^2 = 1/10 + 1 * 1^1 = 11/10
    // t = I a
    // t = 11/10 * 5 = 11/2 = 5.5
    Joint* joint2 = ode.robot->joint(2);
    BOOST_REQUIRE( joint2 );
    VectorN torq = joint2->getComputedTorque();
    
    BOOST_CHECK_CLOSE( torq(0), 5.5, tolPer );
}

BOOST_AUTO_TEST_CASE( testProximalInverseDynamics )
{
    OdeTestHarness ode;

    VectorN ddq(2);
    ddq << 5, 0;
    ode.robot->solveInverseDynamics( ddq );

    // acclerating a m=1, r=0.5 sphere around axis (0,0,1)
    // distal sphere I_aa = 2/5 * m * r^2, around center
    // I_aa = 2/5 * 1 * 0.25 = 2/5 * 1/4 = 2/20 = 1/10
    // I_aa_j1 = 1/10 + m * d^2 = 1/10 + 1 * 3^2 = 1/10 + 9 = 91/10
    // proximal sphere I_bb = 1/10
    // I_bb_j1 = 1/10 + m & d^2 = 1/10 + 1 * 1^2 = 11/10
    // I_aa_j1 + I_bb_j1 = 91/10 + 11/10 = 102/10
    // t = I a
    // t = 102/10 * 5
    // t = 102/2 = 51
    Joint* joint1 = ode.robot->joint(1);
    BOOST_REQUIRE( joint1 );
    VectorN torq = joint1->getComputedTorque();
    BOOST_CHECK_CLOSE( torq(0), 51.0, tolPer );
}



