package jmodbus.server;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class DataBlock {

    private final int mStartAddress;
    private final int mSize;
    private final RegisterSize mRegisterSize;
    private final ByteBuffer mData;

    public DataBlock(int startAddress, int size, RegisterSize registerSize) {
        mStartAddress = startAddress;
        mSize = size;
        mRegisterSize = registerSize;

        mData = ByteBuffer.allocateDirect(size * registerSize.byteSize());
        mData.order(ByteOrder.BIG_ENDIAN);
    }

    protected int getStartAddress() {
        return mStartAddress;
    }

    protected int getSize() {
        return mSize;
    }

    protected ByteBuffer getBuffer() {
        return mData;
    }

    public int offset(int address) {
        if (address < mStartAddress) {
            throw new IllegalArgumentException("address below start address");
        }

        return (address - mStartAddress) * mRegisterSize.byteSize();
    }
}
