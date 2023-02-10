package jmodbus.server;

import java.nio.ByteBuffer;

public class WordDataBlock extends DataBlock {

    public WordDataBlock(int startAddress, int size) {
        super(startAddress, size, RegisterSize.WORD);
    }

    public void put(int address, short value) {
        byte msb = (byte) ((value >> 8) & 0xff);
        byte lsb = (byte) (value & 0xff);

        address = offset(address);
        ByteBuffer buffer = getBuffer();
        buffer.put(address, lsb);
        buffer.put(address + 1, msb);
    }

    public short get(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();

        byte lsb = buffer.get(address);
        byte msb = buffer.get(address + 1);

        return (short) (((msb & 0xff) << 8) | (lsb & 0xff));
    }
}
