cmake_minimum_required (VERSION 3.8)

project( "engine-core-test" )

file( GLOB "SOURCES" "src/*.cpp" )

add_executable( ${PROJECT_NAME} ${SOURCES} )

target_link_libraries( ${PROJECT_NAME} PUBLIC mcgl-engine-core gtest )