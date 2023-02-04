package jmodbus;

public class ModbusTcpJNI {

    public static native long newModbusContext(String ipAddress, int port);
}
