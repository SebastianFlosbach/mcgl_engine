cmake_minimum_required (VERSION 3.8)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

project( "engine-core-test" )

file( GLOB "SOURCES" "src/*.cpp" )

add_executable( ${PROJECT_NAME} ${SOURCES} )
add_test( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} PUBLIC mcgl-engine-core gtest )