
/// Test the tau library
#define BOOST_TEST_MODULE TauTestModule

#include <boost/test/included/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

/// Default percentage error tolerance for floating-point values.
const double tolPer = 1e-5;

/// Testing the tau library.
BOOST_AUTO_TEST_SUITE( tauTestSuite )

/// Testing base constructors and direct accessors. 
BOOST_AUTO_TEST_CASE( testConstructorsAndAccessors )
{
    int i=2;
    BOOST_WARN( false );
    BOOST_CHECK( i == 2 );
}

/// End tests for the tau library.
BOOST_AUTO_TEST_SUITE_END()

