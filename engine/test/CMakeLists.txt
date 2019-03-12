cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine-test" )

file( GLOB "SOURCES" "src/*.h" "src/*.cpp" )

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} PRIVATE mcgl-engine glfw glad glm stb )

install( TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION "bin" )
