package com.qfleng.tcpdemo.socket

class QfServerSocket : AutoCloseable {

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

    /**
     * @param type type 0,tcp;1,udp
     */
    fun openServer(type: Int): String {
        return nOpenServer(mPt, type)
    }

    fun getIpList(): String {
        return nGetIpList(mPt);
    }

    private external fun nCreate(): Long
    private external fun nDestory(nObject: Long)

    private external fun nOpenServer(nObject: Long, type: Int): String
    private external fun nGetIpList(nObject: Long): String

}