package jmodbus.tcp.server;

import jmodbus.ModbusException;
import jmodbus.ModbusIoException;

import java.nio.ByteBuffer;

public class TcpServerTask implements Runnable {

    private final ModbusTcpServer mServer;
    private final ByteBuffer mBuffer;

    public TcpServerTask(ModbusTcpServer server) {
        mServer = server;
        mBuffer = ByteBuffer.allocateDirect(1024);
    }

    @Override
    public void run() {
        while (!Thread.interrupted()) {
            try {
                PendingDataType dataType = mServer.waitForNewData();
                switch (dataType) {
                    case NEW_CLIENT:
                        mServer.accept();
                        break;
                    case NEW_DATA:
                        int read = mServer.readClientRequest(mBuffer);
                        mServer.replayClient(mBuffer, read);
                        break;
                }
            } catch (ModbusIoException e) {
                // close client
                e.printStackTrace();
            } catch (ModbusException e) {
                // continue
                e.printStackTrace();
            }
        }
    }
}
