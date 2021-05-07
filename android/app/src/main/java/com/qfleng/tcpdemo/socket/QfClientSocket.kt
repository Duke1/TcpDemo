package com.qfleng.tcpdemo.socket

class QfClientSocket : AutoCloseable {


    var mPt: Long

    init {
        mPt = nCreate()
    }

    override fun close() {
        try {
            if (mPt > 0) nDestory(mPt)
            mPt = 0
        } finally {

        }
    }

    fun connect(ip: String): String {
        return nConnect(mPt, ip)
    }

    fun send(msg: String) {
        return nSendMsg(mPt, msg)
    }

    private external fun nCreate(): Long
    private external fun nDestory(nObject: Long)

    private external fun nConnect(nObject: Long, ip: String): String
    private external fun nSendMsg(nObject: Long, msg: String)

}