package jmodbus;

import java.nio.ByteBuffer;

public class BufferDataHelper {

    public static void putShort(ByteBuffer buffer, int offset, short value) {
        byte msb = (byte) ((value >> 8) & 0xff);
        byte lsb = (byte) (value & 0xff);

        buffer.put(offset, lsb);
        buffer.put(offset + 1, msb);
    }

    public static short getShort(ByteBuffer buffer, int offset) {
        byte lsb = buffer.get(offset);
        byte msb = buffer.get(offset + 1);

        return (short) (
                ((msb & 0xff) << 8) |
                        (lsb & 0xff));
    }

    public static void putInt(ByteBuffer buffer, int offset, int value) {
        byte d = (byte) ((value >> 24) & 0xff);
        byte c = (byte) ((value >> 16) & 0xff);
        byte b = (byte) ((value >> 8) & 0xff);
        byte a = (byte) (value & 0xff);

        buffer.put(offset, a);
        buffer.put(offset + 1, b);
        buffer.put(offset + 2, c);
        buffer.put(offset + 3, d);
    }

    public static int getInt(ByteBuffer buffer, int offset) {
        byte a = buffer.get(offset);
        byte b = buffer.get(offset + 1);
        byte c = buffer.get(offset + 2);
        byte d = buffer.get(offset + 3);

        return (((d & 0xff) << 24) |
                ((c & 0xff) << 16) |
                ((b & 0xff) << 8) |
                (a & 0xff));
    }

    public static void putFloat(ByteBuffer buffer, int offset, float value) {
        int intValue = Float.floatToIntBits(value);
        putInt(buffer, offset, intValue);
    }

    public static float getFloat(ByteBuffer buffer, int offset) {
        int value = getInt(buffer, offset);
        return Float.intBitsToFloat(value);
    }

    public static void putLong(ByteBuffer buffer, int offset, long value) {
        int msb = (int) (value >> 32);
        int lsb = (int) value;

        putInt(buffer, offset, lsb);
        putInt(buffer, offset + 4, msb);
    }

    public static long getLong(ByteBuffer buffer, int offset) {
        int lsb = getInt(buffer, offset);
        int msb = getInt(buffer, offset + 4);

        return (long) lsb | ((long) msb << 32);
    }

    public static void putDouble(ByteBuffer buffer, int offset, double value) {
        long longValue = Double.doubleToLongBits(value);
        putLong(buffer, offset, longValue);
    }

    public static double getDouble(ByteBuffer buffer, int offset) {
        long value = getLong(buffer, offset);
        return Double.longBitsToDouble(value);
    }
}
