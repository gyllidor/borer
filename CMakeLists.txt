####################################################################################################
CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT( borer )
SET( VERSION 0.0.1 )
#SET(CMAKE_CXX_COMPILER g++)
####################################################################################################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/include/
) # INCLUDE_DIRECTORIES
#
if (${VERBOSE_LOGGER})
add_definitions(-DVERBOSE_LOGGER)
endif (${VERBOSE_LOGGER})
#
set(OBJECTS_DIR ${CMAKE_SOURCE_DIR}/objects/)
set(BINARY_DIR  ${CMAKE_SOURCE_DIR}/objects/bin)
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/objects/lib)
set(LIBRARY_OUTPUT_PATH            ${LIBRARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
#
file(GLOB_RECURSE BORER_SRC ${CMAKE_SOURCE_DIR}/source/*.cpp)
file(GLOB_RECURSE BORER_HDR ${CMAKE_SOURCE_DIR}/include/*.h)
#
add_library(${PROJECT_NAME} STATIC ${BORER_SRC} ${BORER_HDR})
#
if (${UNIT_TESTS})
add_subdirectory(${CMAKE_SOURCE_DIR}/unit_tests/)
endif (${UNIT_TESTS})
