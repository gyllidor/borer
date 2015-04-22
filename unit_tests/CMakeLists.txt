####################################################################################################
PROJECT( test_borer )
####################################################################################################
INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
) # INCLUDE_DIRECTORIES
#
file(GLOB_RECURSE UNIT_TESTS_HDR ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE UNIT_TESTS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
#
add_executable( ${PROJECT_NAME} ${UNIT_TESTS_SRC} ${UNIT_TESTS_HDR})
