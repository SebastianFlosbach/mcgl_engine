cmake_minimum_required (VERSION 3.8)

project( "glad" )

file( GLOB "SOURCES" "src/*.c" "include/glad/*.h" "include/KHR/*.h" )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} )

target_include_directories( ${PROJECT_NAME} PUBLIC "include" )