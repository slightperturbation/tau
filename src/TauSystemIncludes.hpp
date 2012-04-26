//
//  TauSystemIncludes.hpp
//  tau
//
//  External System includes.  Separated to allow the GCC pragma that suppresses
//  warnings.
//
/// Copyright 2010 Brian F. Allen (vector@acm.org). All rights reserved.
//

#pragma GCC system_header

//
#pragma GCC diagnostic push
//#pragma clang diagnostic push


#pragma GCC diagnostic ignored "-Wall"
//#pragma clang ignored "-Wall"
#pragma GCC diagnostic ignored "-Wpedantic"
//#pragma clang ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wconstant-logical-operand"
//#pragma clang ignored "-Wconstant-logical-operand"

#include <Eigen/Core>     // see http://eigen.tuxfamily.org/
#include <Eigen/LU>       // for inverse
#include <Eigen/Geometry> // for cross product

// Only needed for Robot
#include <boost/foreach.hpp>

// Only needed for Ode Implementations
#include <ode/ode.h>

//#pragma clang diagnostic pop
#pragma GCC diagnostic pop


