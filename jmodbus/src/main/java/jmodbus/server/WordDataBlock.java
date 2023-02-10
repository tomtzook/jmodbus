package jmodbus.server;

import java.nio.ByteBuffer;

public class WordDataBlock extends DataBlock {

    public WordDataBlock(int startAddress, int size) {
        super(startAddress, size, RegisterSize.WORD);
    }

    public void putShort(int address, short value) {
        byte msb = (byte) ((value >> 8) & 0xff);
        byte lsb = (byte) (value & 0xff);

        address = offset(address);
        ByteBuffer buffer = getBuffer();
        buffer.put(address, lsb);
        buffer.put(address + 1, msb);
    }

    public short getShort(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();

        byte lsb = buffer.get(address);
        byte msb = buffer.get(address + 1);

        return (short) (
                ((msb & 0xff) << 8) |
                (lsb & 0xff));
    }

    public void putInt(int address, int value) {
        byte d = (byte) ((value >> 24) & 0xff);
        byte c = (byte) ((value >> 16) & 0xff);
        byte b = (byte) ((value >> 8) & 0xff);
        byte a = (byte) (value & 0xff);

        address = offset(address);
        ByteBuffer buffer = getBuffer();
        buffer.put(address, a);
        buffer.put(address + 1, b);
        buffer.put(address + 2, c);
        buffer.put(address + 3, d);
    }

    public int getInt(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();

        byte a = buffer.get(address);
        byte b = buffer.get(address + 1);
        byte c = buffer.get(address + 2);
        byte d = buffer.get(address + 3);

        return (((d & 0xff) << 24) |
                ((c & 0xff) << 16) |
                ((b & 0xff) << 8) |
                (a & 0xff));
    }
}
