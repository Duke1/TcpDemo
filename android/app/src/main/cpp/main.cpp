#include <jni.h>
#include <string>
#include "Base.h"
#include "QfSocket.h"

#include "QfHelper.h"

extern "C" {
JNIEXPORT jstring JNICALL
Java_com_qfleng_tcpdemo_socket_QfSocket_findIpByDomain(JNIEnv *env, jclass clz, jstring domain) {
    std::string d = AndroidHelper::jstringToString(env, domain);
    std::string result = QfHelper::findIpByDomain(d);
    return AndroidHelper::charToJString(env, result.c_str(), result.size());
}
}





//Audio

jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    jclass clazz = NULL;
    JNIEnv *env = NULL;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("JNI_OnLoad->GetEnv error!");
        return -1;
    }

    Qf::regist(env);

    return JNI_VERSION_1_6;
}