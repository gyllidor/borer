####################################################################################################
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( borer )
SET( VERSION 0.0.1 )
####################################################################################################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/include
) # INCLUDE_DIRECTORIES

FILE( GLOB_RECURSE BORER_SRC ${CMAKE_SOURCE_DIR}/source )

add_library( ${PROJECT_NAME} STATIC ${BORER_SRC} )
add_library( ${PROJECT_NAME}static SHARED ${BORER_SRC} )

set_target_properties( ${PROJECT_NAME}static PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
