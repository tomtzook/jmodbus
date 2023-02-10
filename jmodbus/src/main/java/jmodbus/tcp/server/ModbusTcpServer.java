package jmodbus.tcp.server;

import jmodbus.ModbusContextBase;
import jmodbus.server.Registers;

import java.nio.ByteBuffer;

public class ModbusTcpServer extends ModbusContextBase {

    private final long mServerCtxPtr;
    private final Registers mRegisters;

    public ModbusTcpServer(long contextPtr, int backlogSize, Registers registers) {
        super(contextPtr);
        mRegisters = registers;

        try {
            mServerCtxPtr = ModbusTcpServerJNI.init(contextPtr, backlogSize, registers);
        } catch (Throwable t) {
            super.close();
            throw t;
        }
    }

    public Registers getRegisters() {
        return mRegisters;
    }

    public ServerDataUpdate waitForNewData() {
        mLock.lock();
        try {
            verifyNotClosed();

            PendingDataType type = ModbusTcpServerJNI.waitForNewData(mContextPtr, mServerCtxPtr);
            return new ServerDataUpdate(mContextPtr, mServerCtxPtr, type, mLock);
        } finally {
            mLock.unlock();
        }
    }

    @Override
    public void close() {
        mLock.lock();
        try {
            ModbusTcpServerJNI.close(mServerCtxPtr);
            super.close();
        } finally {
            mLock.unlock();
        }
    }
}
