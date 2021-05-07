package com.qfleng.tcpdemo.socket

class QfSocket {
    companion object {
        fun init() {
            System.loadLibrary("c++_shared")
            System.loadLibrary("QfSocket")
        }
    }


    external fun findIpByDomain(domain: String): String
}