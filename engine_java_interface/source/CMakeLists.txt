cmake_minimum_required (VERSION 3.8)

project( "mcgl-engine-java" )

add_library( ${PROJECT_NAME} SHARED "include/MCGLEngineInterface.h" "src/MCGLEngineInterface.cpp"  )
target_link_libraries( ${PROJECT_NAME} PRIVATE mcgl-engine jni )
target_include_directories( ${PROJECT_NAME} PRIVATE "include" )

install( TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION "bin" 
)
