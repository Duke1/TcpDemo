//
// Created by Duke
//

#include <unistd.h>
#include "QfSocket.h"
#include "AndroidHelper.h"

using namespace Qf;

jlong QfClientSocket::create(JNIEnv *env, jobject clazz) {
    QfClientSocket *obj = new QfClientSocket();
    return reinterpret_cast<jlong>(obj);
}

void QfClientSocket::destory(JNIEnv *env, jobject clazz, jlong objHandle) {
    QfClientSocket *obj = reinterpret_cast<QfClientSocket *>(objHandle);
    if (obj)
        delete obj;
}


jstring QfClientSocket::connTo(JNIEnv *env, jobject clazz, jlong objHandle, jstring ip) {

    //返回信息
    Document document;
    document.SetObject();

    QfClientSocket *obj = reinterpret_cast<QfClientSocket *>(objHandle);
    if (obj) {
        obj->conn(AndroidHelper::jstringToString(env, ip));
        vector<string> ips = Qf::getIpAddress(obj->sock);


        //ip数据
        Value ip_list(kArrayType);
        Document::AllocatorType &allocator = document.GetAllocator();
        for (int i = 0; i < ips.size(); i++) {
            ip_list.PushBack(StringRef(ips[i].c_str()), allocator);
        }
        document.AddMember("ip_list", ip_list, allocator);
    }

    StringBuffer strBuffer;
    Writer<StringBuffer> writer(strBuffer);
    document.Accept(writer);

    const char *resultStr = strBuffer.GetString();
    size_t strSize = strlen(resultStr);

    return AndroidHelper::charToJString(env, resultStr, strSize);
}

void QfClientSocket::sendMsg(JNIEnv *env, jobject clazz, jlong objHandle, jstring msg) {

    QfClientSocket *obj = reinterpret_cast<QfClientSocket *>(objHandle);
    if (obj) {
        obj->send(AndroidHelper::jstringToString(env, msg));
    }
}


void QfClientSocket::conn(std::string ip) {

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        LOGI("create socket error! ");
    }


    int str_len;

    struct sockaddr_in serv_adr;
    socklen_t clnt_adr_sz;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == sock) {
        LOGE("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(ip.c_str());
    serv_adr.sin_port = htons(atoi("1313"));

    if (-1 == connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)))
        LOGE("connect() error");


}

void QfClientSocket::send(std::string msg) {
    write(sock, msg.c_str(), msg.size());
    read(sock, message, BUF_SIZE - 1);

    LOGI("client:%s", message);
}

QfClientSocket::~QfClientSocket() {
    close(sock);
}