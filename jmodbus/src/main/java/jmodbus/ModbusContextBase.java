package jmodbus;

import java.io.Closeable;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ModbusContextBase implements Closeable {

    protected final long mContextPtr;
    protected final Lock mLock;
    private boolean mIsClosed;

    public ModbusContextBase(long contextPtr) {
        mContextPtr = contextPtr;
        mLock = new ReentrantLock();
        mIsClosed = false;
    }

    @Override
    public void close() {
        mLock.lock();
        try {
            ModbusJNI.close(mContextPtr);
            ModbusJNI.free(mContextPtr);
            mIsClosed = true;
        } finally {
            mLock.unlock();
        }
    }

    protected void verifyNotClosed() {
        if (mIsClosed) {
            throw new IllegalStateException("already closed");
        }
    }
}
