//
// Created by Duke
//

#include <unistd.h>
#include "QfSocket.h"
#include "AndroidHelper.h"

using namespace Qf;

jlong QfServerSocket::create(JNIEnv *env, jobject clazz) {
    QfServerSocket *obj = new QfServerSocket();
    return reinterpret_cast<jlong>(obj);
}

void QfServerSocket::destory(JNIEnv *env, jobject clazz, jlong objHandle) {
    QfServerSocket *obj = reinterpret_cast<QfServerSocket *>(objHandle);
    if (obj)
        delete obj;
}


jstring QfServerSocket::getIpList(JNIEnv *env, jobject clazz, jlong objHandle) {
    //返回信息
    Document document;
    document.SetObject();

    QfServerSocket *obj = reinterpret_cast<QfServerSocket *>(objHandle);
    if (obj) {
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

void QfServerSocket::openServer(JNIEnv *env, jobject clazz, jlong objHandle, jint type) {

    QfServerSocket *obj = reinterpret_cast<QfServerSocket *>(objHandle);
    if (obj) {

        obj->openTcpServer();

    }

}


void QfServerSocket::openTcpServer() {


    struct sockaddr_in serv_adr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == sock) {
        LOGE("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi("1313"));

    if (-1 == ::bind(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)))
        LOGE("bind() error");

    if (-1 == listen(sock, 5))
        LOGE("listen() error");


    recThread = new std::thread(&QfServerSocket::startAccept, this);
    recThread->detach();


}

void QfServerSocket::startAccept() {

    char message[BUF_SIZE];
    int i;
    int clnt_sock;
    int str_len;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;
    clnt_adr_sz = sizeof(clnt_adr);

    for (i = 0; i < 5; i++) {
        clnt_sock = accept(sock, (struct sockaddr *) &clnt_adr, &clnt_adr_sz);
        if (-1 == clnt_sock)
            LOGE("accept() error");
        else
            LOGI("Connected client %d \n", i + 1);

        while ((str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
            write(clnt_sock, message, str_len);
        }

        close(clnt_sock);
    }
}


QfServerSocket::~QfServerSocket() {
    delete recThread;

    close(sock);
}
