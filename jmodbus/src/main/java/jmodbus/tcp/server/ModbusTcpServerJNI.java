package jmodbus.tcp.server;

import jmodbus.server.Registers;

import java.nio.Buffer;

public class ModbusTcpServerJNI {

    private ModbusTcpServerJNI() {}

    public static native long init(long contextPtr, int backlogSize, Registers registers);
    public static native void close(long serverCtxPtr);

    public static native PendingDataType waitForNewData(long contextPtr, long serverCtxPtr);
    public static native void acceptNewClient(long contextPtr, long serverCtxPtr);
    public static native int readNewClientData(long contextPtr, long serverCtxPtr, Buffer buffer);
    public static native void replyClient(long contextPtr, long serverCtxPtr, Buffer buffer, int size);

    public static native void closeCurrentClient(long contextPtr, long serverCtxPtr);
}
