package jmodbus.tcp.server;

import java.nio.ByteBuffer;
import java.util.concurrent.locks.Lock;

public class ServerDataUpdate {

    private final long mContextPtr;
    private final long mServerCtxPtr;
    private final PendingDataType mType;
    private final Lock mLock;

    public ServerDataUpdate(long contextPtr, long serverCtxPtr, PendingDataType type, Lock lock) {
        mContextPtr = contextPtr;
        mServerCtxPtr = serverCtxPtr;
        mType = type;
        mLock = lock;
    }

    public PendingDataType getType() {
        return mType;
    }

    public void accept() {
        mLock.lock();
        try {
            ModbusTcpServerJNI.acceptNewClient(mContextPtr, mServerCtxPtr);
        } finally {
            mLock.unlock();
        }
    }

    public TcpRequest readClientRequest(ByteBuffer buffer) {
        mLock.lock();
        try {
            if (!buffer.isDirect()) {
                throw new IllegalArgumentException("buffer must be direct");
            }
            if (buffer.isReadOnly()) {
                throw new IllegalArgumentException("buffer must writable");
            }

            int readCount = ModbusTcpServerJNI.readNewClientData(mContextPtr, mServerCtxPtr, buffer);
            return new TcpRequest(mContextPtr, mServerCtxPtr, buffer, readCount, mLock);
        } finally {
            mLock.unlock();
        }
    }

    public void closeCurrentClient() {
        mLock.lock();
        try {
            ModbusTcpServerJNI.closeCurrentClient(mContextPtr, mServerCtxPtr);
        } finally {
            mLock.unlock();
        }
    }
}
