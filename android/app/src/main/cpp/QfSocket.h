//
// Created by Duke
//

#ifndef TCPDEMO_QFSOCKET_H
#define TCPDEMO_QFSOCKET_H

#include "Base.h"
#include <jni.h>
#include <string>
#include "AndroidHelper.h"


#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include "linux/if.h"
#include <string>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#include <thread>

using namespace std;
using namespace rapidjson;

namespace Qf {

#define BUF_SIZE 1024

    static vector<string> getIpAddress(int sock) {
        vector<string> result;

        int i = 0;
        struct ifconf ifconf;
        unsigned char buf[512];
        struct ifreq *ifreq;
        ifconf.ifc_len = 512;
        ifconf.ifc_buf = (char *) buf;

        ioctl(sock, SIOCGIFCONF, &ifconf); //接口信息

        ifreq = (struct ifreq *) buf;

        for (i = (ifconf.ifc_len / sizeof(struct ifreq)); i > 0; i--) {
            char *ip = inet_ntoa(((struct sockaddr_in *) &(ifreq->ifr_addr))->sin_addr);
            result.push_back(ip);
            ifreq++;
        }

        return result;
    }


    class QfClientSocket {
        public:

            int sock;

            char message[BUF_SIZE];
        public:
            static jlong create(JNIEnv *env, jobject clazz);

            static void destory(JNIEnv *env, jobject clazz, jlong objHandle);

            static jstring connTo(JNIEnv *env, jobject clazz, jlong objHandle, jstring ip);

            static void sendMsg(JNIEnv *env, jobject clazz, jlong objHandle, jstring msg);


        public:
            ~QfClientSocket();

            void conn(std::string ip);

            void send(std::string msg);
    };


    class QfServerSocket {


        public:
            int sock;
            std::thread *recThread;
        public:
            static jlong create(JNIEnv *env, jobject clazz);

            static void destory(JNIEnv *env, jobject clazz, jlong objHandle);

            //type 0,tcp;1,udp
            static void openServer(JNIEnv *env, jobject clazz, jlong objHandle, jint type);

            static jstring getIpList(JNIEnv *env, jobject clazz, jlong objHandle);


        public:
            ~QfServerSocket();

            void openTcpServer();

        private:
            void startAccept();
    };


    static void regist(JNIEnv *env) {
        JNINativeMethod methods[] = {{"nCreate",  "()J",                                     (void *) QfClientSocket::create},
                                     {"nDestory", "(J)V",                                    (void *) QfClientSocket::destory},
                                     {"nConnect", "(JLjava/lang/String;)Ljava/lang/String;", (void *) QfClientSocket::connTo},
                                     {"nSendMsg", "(JLjava/lang/String;)V",                  (void *) QfClientSocket::sendMsg},
        };

        AndroidHelper::nativeRegist(env,
                                    "com/qfleng/tcpdemo/socket/QfClientSocket",
                                    methods,
                                    sizeof(methods) / sizeof(methods[0]));


        JNINativeMethod methods1[] = {{"nCreate",     "()J",                    (void *) QfServerSocket::create},
                                      {"nDestory",    "(J)V",                   (void *) QfServerSocket::destory},
                                      {"nOpenServer", "(JI)Ljava/lang/String;", (void *) QfServerSocket::openServer},
                                      {"nGetIpList",  "(J)Ljava/lang/String;",  (void *) QfServerSocket::getIpList},
        };
        AndroidHelper::nativeRegist(env,
                                    "com/qfleng/tcpdemo/socket/QfServerSocket",
                                    methods1,
                                    sizeof(methods1) / sizeof(methods1[0]));
    }
}


#endif //TCPDEMO_QFSOCKET_H


