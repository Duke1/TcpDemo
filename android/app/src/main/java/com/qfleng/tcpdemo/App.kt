package com.qfleng.tcpdemo

import androidx.multidex.MultiDexApplication
import com.qfleng.tcpdemo.socket.QfSocket

class App : MultiDexApplication() {

    override fun onCreate() {
        super.onCreate()

        QfSocket.init()
    }

}