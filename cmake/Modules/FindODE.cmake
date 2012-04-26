# Locate ode
# This module defines
# ODE_LIBRARY
# ODE_FOUND, if false, do not try to link to ode 
# ODE_INCLUDE_DIR, where to find the headers
#
# $ODE_DIR is an environment variable that would
# correspond to the ./configure --prefix=$ODE_DIR
#
# Created by David Guthrie.  Based on code by Robert Osfield

FIND_PATH(ODE_INCLUDE_DIR ode/ode.h
    ${ODE_DIR}/include
    $ENV{ODE_DIR}/include
    $ENV{ODE_DIR}
    ${DELTA3D_EXT_DIR}/inc
    $ENV{DELTA_ROOT}/ext/inc
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/include
    /usr/include
    /usr/include/cal3d
    /sw/include # Fink
    /opt/local/include # DarwinPorts
    /opt/csw/include # Blastwave
    /opt/include
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/include
    /usr/freeware/include
)


MACRO(FIND_ODE_LIBRARY MYLIBRARY MYLIBRARYNAME)

FIND_LIBRARY(${MYLIBRARY}
    NAMES ${MYLIBRARYNAME}
    PATHS
    ${ODE_DIR}/lib
    $ENV{ODE_DIR}/lib
    $ENV{ODE_DIR}
    ${DELTA3D_EXT_DIR}/lib
    $ENV{DELTA_ROOT}/ext/lib
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    [HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\Control\\Session\ Manager\\Environment;OSG_ROOT]/lib
    /usr/freeware/lib64
)

ENDMACRO(FIND_ODE_LIBRARY MYLIBRARY MYLIBRARYNAME)

SET(RELEASE_LIST ode ode_single)
FIND_ODE_LIBRARY(ODE_LIBRARY "${RELEASE_LIST}")

SET(DEBUG_LIST oded ode_singled)
FIND_ODE_LIBRARY(ODE_LIBRARY_DEBUG "${DEBUG_LIST}")

SET(ODE_FOUND "NO")
IF(ODE_LIBRARY AND ODE_INCLUDE_DIR)
    SET(ODE_FOUND "YES")
ENDIF(ODE_LIBRARY AND ODE_INCLUDE_DIR)


# if fails, try using pkg_conf
if(NOT ODE_FOUND)
    include(LibFindMacros)

    # Use pkg-config to get hints about paths
    libfind_pkg_check_modules(ODE_PKGCONF ode)

    # Include dir
    find_path(ODE_INCLUDE_DIR
        NAMES ode/ode.h
        PATHS ${ODE_PKGCONF_INCLUDE_DIRS} ${ODE_INCLUDEDIR}
    )

    # Finally the library itself
    find_library(ODE_LIBRARY
        NAMES ode
        PATHS ${ODE_PKGCONF_LIBRARY_DIRS} ${ODE_LIBRARYDIR}
    )

    # Set the include dir variables and the libraries and let libfind_process do the rest.
    # NOTE: Singular variables for this library, plural for libraries this this lib depends on.
    set(ODE_PROCESS_INCLUDES ODE_INCLUDE_DIR)
    set(ODE_PROCESS_LIBS ODE_LIBRARY)

    libfind_process(ODE)
endif(NOT ODE_FOUND)

