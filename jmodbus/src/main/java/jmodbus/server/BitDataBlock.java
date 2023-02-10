package jmodbus.server;

import java.nio.ByteBuffer;

public class BitDataBlock extends DataBlock {

    public BitDataBlock(int startAddress, int size) {
        super(startAddress, size, RegisterSize.BIT);
    }

    public void putBit(int address, boolean value) {
        getBuffer().put(offset(address), (byte) (value ? 1 : 0));
    }

    public boolean getBit(int address) {
        return getBuffer().get(offset(address)) != 0;
    }

    public void putBits(int address, int count, long bits) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();

        for (int i = 0; i < count; i++) {
            buffer.put(address + i, (byte) ((bits & (1L << i)) != 0 ? 1 : 0));
        }
    }

    public long getBits(int address, int count) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();

        long value = 0;
        for (int i = 0; i < count; i++) {
            byte b = buffer.get(address + i);
            value |= ((long) b << i);
        }

        return value;
    }
}
