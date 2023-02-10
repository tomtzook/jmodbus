package jmodbus.tcp.server;

import jmodbus.server.RequestBase;

import java.nio.ByteBuffer;
import java.util.concurrent.locks.Lock;

public class TcpRequest extends RequestBase {

    private final Lock mLock;
    private final long mServerCtxPtr;

    public TcpRequest(long contextPtr, long serverCtxPtr, ByteBuffer buffer, int size, Lock lock) {
        super(contextPtr, buffer, size);
        mServerCtxPtr = serverCtxPtr;
        mLock = lock;
    }

    public void reply() {
        mLock.lock();
        try {
            ModbusTcpServerJNI.replyClient(mContextPtr, mServerCtxPtr, getBuffer(), getSize());
        } finally {
            mLock.unlock();
        }
    }
}
