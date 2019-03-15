cmake_minimum_required (VERSION 3.8)

project( "mcgl_engine_java" )

add_library( ${PROJECT_NAME} SHARED "MCGLEngineInterface.h" "MCGLEngineInterface.cpp"  )
target_link_libraries( ${PROJECT_NAME} PRIVATE mcgl-engine_static jni )
