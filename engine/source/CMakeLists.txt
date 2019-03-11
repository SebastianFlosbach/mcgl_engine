cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine" )

file( GLOB "SOURCES" "src/*.h" "src/*.cpp" "include/*.h" "include/*.cpp" )

add_library( ${PROJECT_NAME} SHARED ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PUBLIC "include" )
target_link_libraries( ${PROJECT_NAME} PRIVATE glfw glad glm stb )

install( TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION "bin" )
