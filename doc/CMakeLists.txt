# Tau Documentation build
#

IF( SHOULD_BUILD_TAU_DOCUMENTATION )
    FIND_PACKAGE(Doxygen)
    IF(DOXYGEN_FOUND)
        
        # Optionally reference external images for docs
        SET( CMAKE_DOXYGEN_IMAGE_PATH
            "${CMAKE_CURRENT_SOURCE_DIR}/img"
        )
        # doxygen searches for source code (defined in FILE_PATTERNS, for example: *.cpp *.h)
        # with DOXYGEN_SOURCE_DIR we fill a list of directories and later we write it into
        # the Doxyfile with a REGEX REPLACE (see below)
        SET( DOXYGEN_SOURCE_DIR
            "${CMAKE_SOURCE_DIR}/src"
        )

        SET(DOXYGEN_OUTPUT_DIR html)
        STRING(REGEX REPLACE ";" " " CMAKE_DOXYGEN_INPUT_LIST "${DOXYGEN_SOURCE_DIR}")

        # Allow configuration variables to be used in the doxygen.config file 
        # (e.g. @PROJECT_VERSION@ for version number)
        CONFIGURE_FILE(doxygen.config.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config)
        SET(HTML_TARGET "html" )

        ADD_CUSTOM_TARGET(${HTML_TARGET} ALL
                    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config
                    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/doxygen.config)

        INSTALL( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "/usr/share/doc/libtau-${LIBTAU_VERSION}" )

    ELSE(DOXYGEN_FOUND)
        MESSAGE (FATAL_ERROR "doxygen binary couldn't be found")
    ENDIF(DOXYGEN_FOUND)
ENDIF( SHOULD_BUILD_TAU_DOCUMENTATION )