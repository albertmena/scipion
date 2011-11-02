/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class xmipp_TiltPairAligner */

#ifndef _Included_xmipp_TiltPairAligner
#define _Included_xmipp_TiltPairAligner
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_storeIds(JNIEnv *env,
		jclass cls);

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_create(JNIEnv *env,
		jobject jobj);

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_destroy(JNIEnv *env,
		jobject jobj);

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_clear(JNIEnv *env,
		jobject jobj);
/*
 * Class:     xmipp_TiltPairAligner
 * Method:    addParticleToAligner
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_addParticleToAligner
  (JNIEnv *, jobject, jint, jint, jint, jint);

/*
 * Class:     xmipp_TiltPairAligner
 * Method:    getTiltedParticle
 * Signature: (II)
 */
JNIEXPORT jobject JNICALL Java_xmipp_TiltPairAligner_getTiltedParticle
  (JNIEnv *, jobject, jint, jint);


JNIEXPORT jintArray JNICALL Java_xmipp_TiltPairAligner_computeAlphas(JNIEnv *env,
		jobject jobj);

#ifdef __cplusplus
}
#endif
#endif
