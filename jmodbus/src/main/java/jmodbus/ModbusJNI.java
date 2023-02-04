package jmodbus;

public class ModbusJNI {

    public static native void free(long contextPtr);

    public static native void connect(long contextPtr);
    public static native void flush(long contextPtr);
    public static native void close(long contextPtr);

    public static native void setDebug(long contextPtr, boolean isEnabled);

    public static native void setSlave(long contextPtr, int slave);
    public static native int getSlave(long contextPtr);

    public static native boolean[] readCoils(long contextPtr, int address, int count);
    public static native boolean[] readDiscreteInputs(long contextPtr, int address, int count);
    public static native short[] readInputRegisters(long contextPtr, int address, int count);
    public static native short[] readHoldingRegisters(long contextPtr, int address, int count);

    public static native void writeCoil(long contextPtr, int address, boolean value);
    public static native void writeCoils(long contextPtr, int address, int count, boolean[] values);
    public static native void writeHoldingRegister(long contextPtr, int address, short value);
    public static native void writeHoldingRegisters(long contextPtr, int address, int count, short[] values);
}
