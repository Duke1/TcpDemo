//
// Created by Duke
//

#ifndef __ANDROIDHELPER_H__
#define __ANDROIDHELPER_H__

#include "Base.h"
#include <string>

class AndroidHelper {
    public:
        static jstring charToJString(JNIEnv *env, const char *data, size_t len);

        static std::string jstringToString(JNIEnv *env, jstring inputStr);

        static void
        nativeRegist(JNIEnv *env, const char *className, const JNINativeMethod *methods, size_t methodSize);
};


#endif //__ANDROIDHELPER_H__
