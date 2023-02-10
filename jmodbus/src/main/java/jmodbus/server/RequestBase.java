package jmodbus.server;

import jmodbus.ModbusJNI;

import java.nio.ByteBuffer;

public class RequestBase {

    protected final long mContextPtr;
    private final ByteBuffer mBuffer;
    private final int mSize;

    public RequestBase(long contextPtr, ByteBuffer buffer, int size) {
        mContextPtr = contextPtr;
        mBuffer = buffer;
        mSize = size;
    }

    public ByteBuffer getBuffer() {
        return mBuffer;
    }

    public int getSize() {
        return mSize;
    }

    public int getHeaderLength() {
        return ModbusJNI.getHeaderLength(mContextPtr);
    }

    public int getSlave() {
        return mBuffer.get(getHeaderLength() - 1);
    }

    public int getFunction() {
        return mBuffer.get(getHeaderLength());
    }

    public int getAddress() {
        int offset = getHeaderLength();
        int msb = mBuffer.get(offset + 1);
        int lsb = mBuffer.get(offset + 2);

        return (msb << 8) | lsb;
    }
}
