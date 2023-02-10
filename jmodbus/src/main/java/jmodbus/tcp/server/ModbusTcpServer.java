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

    public PendingDataType waitForNewData() {
        mLock.lock();
        try {
            verifyNotClosed();

            return ModbusTcpServerJNI.waitForNewData(mContextPtr, mServerCtxPtr);
        } finally {
            mLock.unlock();
        }
    }

    public void accept() {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusTcpServerJNI.acceptNewClient(mContextPtr, mServerCtxPtr);
        } finally {
            mLock.unlock();
        }
    }

    public int readClientRequest(ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            if (!buffer.isDirect()) {
                throw new IllegalArgumentException("buffer must be direct");
            }
            if (buffer.isReadOnly()) {
                throw new IllegalArgumentException("buffer must writable");
            }

            return ModbusTcpServerJNI.readNewClientData(mContextPtr, mServerCtxPtr, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void replyClient(ByteBuffer requestBuffer, int requestSize) {
        mLock.lock();
        try {
            verifyNotClosed();
            if (!requestBuffer.isDirect()) {
                throw new IllegalArgumentException("buffer must be direct");
            }
            if (requestBuffer.isReadOnly()) {
                throw new IllegalArgumentException("buffer must writable");
            }

            ModbusTcpServerJNI.replyClient(mContextPtr, mServerCtxPtr, requestBuffer, requestSize);
        } finally {
            mLock.unlock();
        }
    }

    public void closeCurrentClient() {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusTcpServerJNI.closeCurrentClient(mContextPtr, mServerCtxPtr);
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
