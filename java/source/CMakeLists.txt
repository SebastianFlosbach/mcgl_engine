cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine-java" )

file( GLOB_RECURSE "SOURCES" "*.h" "*.cpp" )

add_library( ${PROJECT_NAME} SHARED ${SOURCES} )
target_link_libraries( ${PROJECT_NAME} PRIVATE mcgl-engine jni )
target_include_directories( ${PROJECT_NAME} PRIVATE "include" )

install( TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION "bin" 
)
