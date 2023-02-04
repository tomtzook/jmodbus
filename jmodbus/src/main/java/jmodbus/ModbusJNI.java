package jmodbus;

import java.nio.Buffer;

public class ModbusJNI {

    private ModbusJNI() {}

    public static native void free(long contextPtr);

    public static native void connect(long contextPtr);
    public static native void flush(long contextPtr);
    public static native void close(long contextPtr);

    public static native void setDebug(long contextPtr, boolean isEnabled);

    public static native void setSlave(long contextPtr, int slave);
    public static native int getSlave(long contextPtr);

    public static native void readCoils(long contextPtr, int address, int count, boolean[] buffer);
    public static native long readCoils2(long contextPtr, int address, int count);
    public static native void readCoils3(long contextPtr, int address, int count, Buffer buffer);
    public static native void readCoils4(long contextPtr, int address, int count, byte[] buffer);

    public static native void readDiscreteInputs(long contextPtr, int address, int count, boolean[] buffer);
    public static native long readDiscreteInputs2(long contextPtr, int address, int count);
    public static native void readDiscreteInputs3(long contextPtr, int address, int count, Buffer buffer);
    public static native void readDiscreteInputs4(long contextPtr, int address, int count, byte[] buffer);

    public static native void readInputRegisters(long contextPtr, int address, int count, short[] buffer);
    public static native void readInputRegisters2(long contextPtr, int address, int count, Buffer buffer);
    public static native void readInputRegisters3(long contextPtr, int address, int count, byte[] buffer);

    public static native void readHoldingRegisters(long contextPtr, int address, int count, short[] buffer);
    public static native void readHoldingRegisters2(long contextPtr, int address, int count, Buffer buffer);
    public static native void readHoldingRegisters3(long contextPtr, int address, int count, byte[] buffer);

    public static native void writeCoil(long contextPtr, int address, boolean value);
    public static native void writeCoil2(long contextPtr, int address, byte value);

    public static native void writeCoils(long contextPtr, int address, int count, boolean[] values);
    public static native void writeCoils2(long contextPtr, int address, int count, long value);
    public static native void writeCoils3(long contextPtr, int address, int count, byte[] values);
    public static native void writeCoils4(long contextPtr, int address, int count, Buffer buffer);

    public static native void writeHoldingRegister(long contextPtr, int address, short value);
    public static native void writeHoldingRegisters(long contextPtr, int address, int count, short[] values);
    public static native void writeHoldingRegisters2(long contextPtr, int address, int count, Buffer buffer);
}
