cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine" )

file( GLOB "SOURCES"	"../libs/include/*.h" "../libs/include/*.cpp"
						"../libs/src/*.h" "../libs/src/*.cpp"
						"include/*.h" "include/*.cpp"
						"src/*.h" "src/*.cpp"
)

include_directories( "../libs/include" )

add_library( ${PROJECT_NAME} SHARED ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PUBLIC "include" )
target_link_libraries( ${PROJECT_NAME} PRIVATE glfw glad glm stb )

install( TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION "bin" )
