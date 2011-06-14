/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class xmipp_MetaData */

#ifndef _Included_xmipp_MetaData
#define _Included_xmipp_MetaData
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     xmipp_MetaData
 * Method:    storeIds
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_storeIds
  (JNIEnv *, jclass);

/*
 * Class:     xmipp_MetaData
 * Method:    create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_create
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_destroy
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    read
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_read
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    size
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_xmipp_MetaData_size
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    write
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_write
  (JNIEnv *, jobject, jstring);

/*
 * Class:     xmipp_MetaData
 * Method:    print
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_print
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    containsLabel
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_MetaData_containsLabel
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    label2Str
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_xmipp_MetaData_label2Str
  (JNIEnv *, jobject, jint);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueInt
 * Signature: (IJ)I
 */
JNIEXPORT jint JNICALL Java_xmipp_MetaData_getValueInt
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueDouble
 * Signature: (IJ)D
 */
JNIEXPORT jdouble JNICALL Java_xmipp_MetaData_getValueDouble
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueString
 * Signature: (IJ)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_xmipp_MetaData_getValueString
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getValueBoolean
 * Signature: (IJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_MetaData_getValueBoolean
  (JNIEnv *, jobject, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    getFilename
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_xmipp_MetaData_getFilename
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueInt
 * Signature: (IIJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_MetaData_setValueInt
  (JNIEnv *, jobject, jint, jint, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueDouble
 * Signature: (IDJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_MetaData_setValueDouble
  (JNIEnv *, jobject, jint, jdouble, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueString
 * Signature: (ILjava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_MetaData_setValueString
  (JNIEnv *, jobject, jint, jstring, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    setValueBoolean
 * Signature: (IZJ)Z
 */
JNIEXPORT jboolean JNICALL Java_xmipp_MetaData_setValueBoolean
  (JNIEnv *, jobject, jint, jboolean, jlong);

/*
 * Class:     xmipp_MetaData
 * Method:    findObjects
 * Signature: ()[J
 */
JNIEXPORT jlongArray JNICALL Java_xmipp_MetaData_findObjects
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    addObject
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_xmipp_MetaData_addObject
  (JNIEnv *, jobject);

/*
 * Class:     xmipp_MetaData
 * Method:    addLabel
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_xmipp_MetaData_addLabel
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
