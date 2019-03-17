cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine-core" )

file( GLOB_RECURSE "SOURCES" "*.h" "*.cpp" )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PUBLIC "include" )
target_link_libraries( ${PROJECT_NAME} PUBLIC glfw glad glm stb )
