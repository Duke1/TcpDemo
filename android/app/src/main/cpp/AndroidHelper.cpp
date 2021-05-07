//
// Created by Duke
//

#include "AndroidHelper.h"


jstring AndroidHelper::charToJString(JNIEnv *env, const char *data, size_t len) {
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array, 0, len, (const jbyte *) data);
    jstring strEncode = env->NewStringUTF("UTF-8");
    jclass cls = env->FindClass("java/lang/String");
    jmethodID ctor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;)V");
    jstring object = (jstring) env->NewObject(cls, ctor, array, strEncode);
    return object;
}

std::string AndroidHelper::jstringToString(JNIEnv *env, jstring inputStr) {

    const char *tmpChar = env->GetStringUTFChars(inputStr, JNI_FALSE);
    std::string result(tmpChar);
    env->ReleaseStringUTFChars(inputStr, tmpChar);

    return result;
}

void
AndroidHelper::nativeRegist(JNIEnv *env, const char *className, const JNINativeMethod *methods, size_t methodSize) {
    jclass clazz = env->FindClass(className);
    if (!clazz) {
        LOGE("JNI_OnLoad->FindClass (%s) error!", className);
        return;
    }
    if (env->RegisterNatives(clazz, methods, methodSize) < 0) {
        LOGE("JNI_OnLoad->RegisterNatives error!");
        return;
    }
}