package com.qfleng.tcpdemo

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.text.method.ScrollingMovementMethod
import android.util.Log
import com.qfleng.tcpdemo.databinding.ActivityMainBinding
import com.qfleng.tcpdemo.socket.QfClientSocket
import com.qfleng.tcpdemo.socket.QfServerSocket
import com.qfleng.tcpdemo.socket.QfSocket

class MainActivity : AppCompatActivity() {
    val vBinding by lazy {
        ActivityMainBinding.inflate(layoutInflater)
    }

    val socket = QfSocket()
    val serverSocket = QfServerSocket()
    val clientSocket = QfClientSocket()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(vBinding.root)

        vBinding.btnOpenServer.setOnClickListener {
            serverSocket.openServer(0)
            val result = serverSocket.getIpList()
            vBinding.serverDisplayView.append(result)
        }
        vBinding.btnCloseServer.setOnClickListener {
            serverSocket.close()
        }

        vBinding.btnConnectServer.setOnClickListener {
            val result = clientSocket.connect(vBinding.ipAddress.text.toString())
            vBinding.clientDisplayView.append(result)
        }
        vBinding.btnClientSend.setOnClickListener {
            val msg = vBinding.clientInput.text.toString()
            clientSocket.send(msg)
        }
        vBinding.btnDomainInfo.setOnClickListener {
            val result = socket.findIpByDomain(vBinding.ipAddress.text.toString())
            vBinding.clientDisplayView.append(result)
        }

        vBinding.serverDisplayView.movementMethod = ScrollingMovementMethod.getInstance()
        vBinding.clientDisplayView.movementMethod = ScrollingMovementMethod.getInstance()
    }


}