/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class xmipp_ImageGeneric */

#ifndef _Included_xmipp_jni_ImageGeneric
#define _Included_xmipp_jni_ImageGeneric
#ifdef __cplusplus
extern "C" {
#endif
#undef xmipp_ImageGeneric_FIRST_IMAGE
#define xmipp_ImageGeneric_FIRST_IMAGE 1LL
#undef xmipp_ImageGeneric_FIRST_SLICE
#define xmipp_ImageGeneric_FIRST_SLICE 1L
#undef xmipp_ImageGeneric_ALL_IMAGES
#define xmipp_ImageGeneric_ALL_IMAGES 0LL
#undef xmipp_ImageGeneric_ALL_SLICES
#define xmipp_ImageGeneric_ALL_SLICES 0L
#undef xmipp_ImageGeneric_MID_SLICE
#define xmipp_ImageGeneric_MID_SLICE -1L
#undef xmipp_ImageGeneric_Default
#define xmipp_ImageGeneric_Default -1L
#undef xmipp_ImageGeneric_Unknown_Type
#define xmipp_ImageGeneric_Unknown_Type 0L
#undef xmipp_ImageGeneric_UChar
#define xmipp_ImageGeneric_UChar 1L
#undef xmipp_ImageGeneric_SChar
#define xmipp_ImageGeneric_SChar 2L
#undef xmipp_ImageGeneric_UShort
#define xmipp_ImageGeneric_UShort 3L
#undef xmipp_ImageGeneric_Short
#define xmipp_ImageGeneric_Short 4L
#undef xmipp_ImageGeneric_UInt
#define xmipp_ImageGeneric_UInt 5L
#undef xmipp_ImageGeneric_Int
#define xmipp_ImageGeneric_Int 6L
#undef xmipp_ImageGeneric_Long
#define xmipp_ImageGeneric_Long 7L
#undef xmipp_ImageGeneric_Float
#define xmipp_ImageGeneric_Float 8L
#undef xmipp_ImageGeneric_Double
#define xmipp_ImageGeneric_Double 9L
#undef xmipp_ImageGeneric_ComplexShort
#define xmipp_ImageGeneric_ComplexShort 10L
#undef xmipp_ImageGeneric_ComplexInt
#define xmipp_ImageGeneric_ComplexInt 11L
#undef xmipp_ImageGeneric_ComplexFloat
#define xmipp_ImageGeneric_ComplexFloat 12L
#undef xmipp_ImageGeneric_ComplexDouble
#define xmipp_ImageGeneric_ComplexDouble 13L
#undef xmipp_ImageGeneric_Bool
#define xmipp_ImageGeneric_Bool 14L
#undef xmipp_ImageGeneric_LastEntry
#define xmipp_ImageGeneric_LastEntry 15L
/*
 * Class:     xmipp_ImageGeneric
 * Method:    create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_create
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_destroy
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    resize
 * Signature: (IIIJ)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_resize
  (JNIEnv *, jobject, jint, jint, jint, jlong);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getXDim
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_ImageGeneric_getXDim
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getYDim
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_ImageGeneric_getYDim
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getZDim
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_ImageGeneric_getZDim
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getNDim
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_xmipp_jni_ImageGeneric_getNDim
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getDataType
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_xmipp_jni_ImageGeneric_getDataType
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    readHeader
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_readHeader
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    read
 * Signature: (Ljava/lang/String;IIIJ)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_read
  (JNIEnv *, jobject, jstring, jint, jint, jint, jlong);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    readApplyGeo_
 * Signature: (Ljava/lang/String;Lxmipp/MetaData;JII)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_readApplyGeo_1
  (JNIEnv *, jobject, jstring, jobject, jlong, jint, jint, jboolean);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getArrayByte
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_xmipp_jni_ImageGeneric_getArrayByte
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getArrayShort
 * Signature: (I)[S
 */
JNIEXPORT jshortArray JNICALL Java_xmipp_jni_ImageGeneric_getArrayShort
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    getArrayFloat
 * Signature: (I)[F
 */
JNIEXPORT jfloatArray JNICALL Java_xmipp_jni_ImageGeneric_getArrayFloat
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    setArrayByte
 * Signature: ([BI)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_setArrayByte
  (JNIEnv *, jobject, jbyteArray, jlong, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    setArrayShort
 * Signature: ([SI)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_setArrayShort
  (JNIEnv *, jobject, jshortArray, jlong, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    setArrayFloat
 * Signature: ([FI)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_setArrayFloat
  (JNIEnv *, jobject, jfloatArray, jlong, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    setDataType
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_setDataType
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    convert2Datatype
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_convert2Datatype
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    mapFile2Write
 * Signature: (IIILjava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_mapFile2Write
  (JNIEnv *, jobject, jint, jint, jint, jstring, jlong);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    write
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_write
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    printShape
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_printShape
  (JNIEnv *, jobject);

/*
   * Class:     xmipp_ImageGeneric
   * Method:    equal
   * Signature: bool
   */
  JNIEXPORT jboolean JNICALL Java_xmipp_jni_ImageGeneric_equal
    (JNIEnv *, jobject ,jobject , jdouble );
/*
   * Class:     xmipp_ImageGeneric
   * Method:    subtract
   * Signature: void 
   */

   JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_subtract
     (JNIEnv *, jobject, jobject, jobject);

/*
* Class:     xmipp_ImageGeneric
* Method:    smooth
* Signature: void
*/

  JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_smooth
        (JNIEnv *, jobject, jobject);
/*
 * Class:     xmipp_ImageGeneric
 * Method:    getStatistics
 * Signature: ()[D
 */
JNIEXPORT jdoubleArray JNICALL Java_xmipp_jni_ImageGeneric_getStatistics
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    setXmippOrigin
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_setXmippOrigin
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    convertPSD
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_convertPSD
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    reslice
 * Signature: (Z,Z,I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_getReslice
  (JNIEnv *, jobject, jobject, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    reslice
 * Signature: (Z,Z,I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_reslice
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_ImageGeneric
 * Method:    reslice
 * Signature: (Z,Z,I)V
 */
JNIEXPORT void JNICALL Java_xmipp_jni_ImageGeneric_getPreview
  (JNIEnv *, jobject, jobject, jint, jint, jint, jlong);

#ifdef __cplusplus
}
#endif
#endif
