/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class MCGLEngine */

#ifndef _Included_MCGLEngine
#define _Included_MCGLEngine
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     MCGLEngine
 * Method:    CreateEngine
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_CreateEngine
  (JNIEnv *, jobject);

/*
 * Class:     MCGLEngine
 * Method:    DestroyEngine
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_DestroyEngine
  (JNIEnv *, jobject);

/*
 * Class:     MCGLEngine
 * Method:    CreateWindow
 * Signature: (IILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_CreateWindow
  (JNIEnv *, jobject, jint, jint, jstring);

/*
 * Class:     MCGLEngine
 * Method:    CloseWindow
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_CloseWindow
  (JNIEnv *, jobject);

/*
 * Class:     MCGLEngine
 * Method:    Run
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_Run
  (JNIEnv *, jobject);

/*
 * Class:     MCGLEngine
 * Method:    Stop
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_Stop
  (JNIEnv *, jobject);

/*
 * Class:     MCGLEngine
 * Method:    RegisterBlockType
 * Signature: (LBlock;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_RegisterBlockType
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MCGLEngine
 * Method:    SetTextures
 * Signature: (Ljava/lang/String;II)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_SetTextures
  (JNIEnv *, jobject, jstring, jint, jint);

/*
 * Class:     MCGLEngine
 * Method:    SetShader
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_SetShader
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     MCGLEngine
 * Method:    AddChunk
 * Signature: (LChunk;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_AddChunk
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MCGLEngine
 * Method:    RemoveChunk
 * Signature: (LChunkCoordinates;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_RemoveChunk
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MCGLEngine
 * Method:    CreateCamera
 * Signature: (DDDDDD)I
 */
JNIEXPORT jint JNICALL Java_MCGLEngine_CreateCamera
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jdouble, jdouble);

/*
 * Class:     MCGLEngine
 * Method:    MoveCamera
 * Signature: (IDDD)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_MoveCamera
  (JNIEnv *, jobject, jint, jdouble, jdouble, jdouble);

/*
 * Class:     MCGLEngine
 * Method:    RotateCamera
 * Signature: (IDDD)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_RotateCamera
  (JNIEnv *, jobject, jint, jdouble, jdouble, jdouble);

/*
 * Class:     MCGLEngine
 * Method:    RegisterKeyEventCallback
 * Signature: (LIKeyEventCallback;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_RegisterKeyEventCallback
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MCGLEngine
 * Method:    RegisterMouseEventCallback
 * Signature: (LIMouseEventCallback;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_RegisterMouseEventCallback
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MCGLEngine
 * Method:    RegisterStatusEventCallback
 * Signature: (LIStatusEventCallback;)V
 */
JNIEXPORT void JNICALL Java_MCGLEngine_RegisterStatusEventCallback
  (JNIEnv *, jobject, jobject);

/*
 * Class:     MCGLEngine
 * Method:    GetDeltaTime
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_MCGLEngine_GetDeltaTime
  (JNIEnv *, jobject);

/*
 * Class:     MCGLEngine
 * Method:    GetCameraPosition
 * Signature: (I)LWorldCoordinates;
 */
JNIEXPORT jobject JNICALL Java_MCGLEngine_GetCameraPosition
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif