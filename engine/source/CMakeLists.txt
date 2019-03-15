cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine" )

file( GLOB "SOURCES"	"include/*.h" "include/*.cpp"
						"src/*.h" "src/*.cpp"
)


add_library( ${PROJECT_NAME} SHARED ${SOURCES} )
add_library( "${PROJECT_NAME}_static" STATIC ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PUBLIC "include" )
target_include_directories( "${PROJECT_NAME}_static" PUBLIC "include" )
target_link_libraries( ${PROJECT_NAME} PRIVATE mcgl-engine-core glfw glad glm stb )
target_link_libraries( "${PROJECT_NAME}_static" PRIVATE mcgl-engine-core glfw glad glm stb )

install( TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION "bin" )
