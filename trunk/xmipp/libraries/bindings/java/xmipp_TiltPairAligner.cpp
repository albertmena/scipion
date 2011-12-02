/*
 * xmipp_TiltPairAligner.cpp
 *
 *  Created on: Sep 20, 2011
 *      Author: airen
 */
#include <jni.h>
#include "xmipp_TiltPairAligner.h"
#include "data/micrograph.h"
#include "xmipp_ExceptionsHandler.h"
#include "xmipp_InternalData.h"

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_storeIds(JNIEnv *env,
		jclass cls) {
	TiltPairAligner_peerId = env->GetFieldID(cls, "peer", "J");
}

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_create(JNIEnv *env,
		jobject jobj) {
	TiltPairAligner * tpa = new TiltPairAligner();
	env->SetLongField(jobj, TiltPairAligner_peerId, (long) tpa);
}

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_destroy(JNIEnv *env,
		jobject jobj) {
	TiltPairAligner * tpa = GET_INTERNAL_TPA(jobj);
	delete tpa;
	tpa = NULL;
	env->SetLongField(jobj, TiltPairAligner_peerId, (long) tpa);
}

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_addParticleToAligner(
		JNIEnv * env, jobject jobj, jint jx1, jint jy1, jint jx2, jint jy2) {

	String msg;
	TiltPairAligner * tpa = GET_INTERNAL_TPA(jobj);
	if (tpa != NULL) {
		try {
			tpa->adjustPassingMatrix(jx1, jy1, jx2, jy2);
		} catch (XmippError xe) {
			msg = xe.getDefaultMessage();
		} catch (std::exception& e) {
			msg = e.what();
		} catch (...) {
			msg = "Unhandled exception";
		}
	} else {
		msg = "TiltPairAligner is null";
	}

	// If there was an exception, sends it to java environment.
	if (!msg.empty()) {
		handleXmippException(env, msg);
	}

}

JNIEXPORT jobject JNICALL Java_xmipp_TiltPairAligner_getTiltedParticle(
		JNIEnv *env, jobject jobj, jint jx1, jint jy1) {
	String msg;

	try {
		int x = 0, y = 0;
		TiltPairAligner * tpa = GET_INTERNAL_TPA(jobj);
		if (tpa != NULL) {
			tpa->passToTilted(jx1, jy1, x, y);
			jclass pclass = env->FindClass("xmipp/Particle");

			jmethodID constructor = env->GetMethodID(pclass, "<init>", "(II)V");
			jobject particle = env->NewObject(pclass, constructor, x, y);
			return particle;
		} else {
			msg = "TiltPairAligner is null";
		}
	} catch (XmippError xe) {
		msg = xe.getDefaultMessage();
	} catch (std::exception& e) {
		msg = e.what();
	} catch (...) {
		msg = "Unhandled exception";
	}

	// If there was an exception, sends it to java environment.
	if (!msg.empty()) {
		handleXmippException(env, msg);
	}
}

JNIEXPORT void JNICALL Java_xmipp_TiltPairAligner_clear(JNIEnv *env,
		jobject jobj) {
	String msg;

	try {
		TiltPairAligner * tpa = GET_INTERNAL_TPA(jobj);
		if (tpa != NULL) {
			tpa->clear();
		} else {
			msg = "TiltPairAligner is null";
		}
	} catch (XmippError xe) {
		msg = xe.getDefaultMessage();
	} catch (std::exception& e) {
		msg = e.what();
	} catch (...) {
		msg = "Unhandled exception";
	}

	// If there was an exception, sends it to java environment.
	if (!msg.empty()) {
		handleXmippException(env, msg);
	}
}

JNIEXPORT jintArray JNICALL Java_xmipp_TiltPairAligner_computeAlphas(JNIEnv *env,
		jobject jobj) {
	String msg;

	try {
		TiltPairAligner * tpa = GET_INTERNAL_TPA(jobj);
		if (tpa != NULL) {
			int alphas[3];
			tpa->computeAngles(alphas[0], alphas[1], alphas[2]);
			jintArray result = env->NewIntArray(2);
			env->SetIntArrayRegion(result, 0, 3, alphas);
			return result;
		} else {
			msg = "TiltPairAligner is null";
		}
	} catch (XmippError xe) {
		msg = xe.getDefaultMessage();
	} catch (std::exception& e) {
		msg = e.what();
	} catch (...) {
		msg = "Unhandled exception";
	}

	// If there was an exception, sends it to java environment.
	if (!msg.empty()) {
		handleXmippException(env, msg);
	}
}

