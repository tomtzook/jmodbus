package jmodbus.server;

import jmodbus.BufferDataHelper;

import java.nio.ByteBuffer;

public class WordDataBlock extends DataBlock {

    public WordDataBlock(int startAddress, int size) {
        super(startAddress, size, RegisterSize.WORD);
    }

    public void putShort(int address, short value) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        BufferDataHelper.putShort(buffer, address, value);
    }

    public short getShort(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        return BufferDataHelper.getShort(buffer, address);
    }

    public void putInt(int address, int value) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        BufferDataHelper.putInt(buffer, address, value);
    }

    public int getInt(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        return BufferDataHelper.getInt(buffer, address);
    }

    public void putFloat(int address, float value) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        BufferDataHelper.putFloat(buffer, address, value);
    }

    public float getFloat(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        return BufferDataHelper.getFloat(buffer, address);
    }

    public void putLong(int address, long value) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        BufferDataHelper.putLong(buffer, address, value);
    }

    public long getLong(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        return BufferDataHelper.getLong(buffer, address);
    }

    public void putDouble(int address, double value) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        BufferDataHelper.putDouble(buffer, address, value);
    }

    public double getDouble(int address) {
        address = offset(address);
        ByteBuffer buffer = getBuffer();
        return BufferDataHelper.getDouble(buffer, address);
    }
}
