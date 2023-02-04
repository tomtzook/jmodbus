package jmodbus;

public class ModbusTcpJNI {

    private ModbusTcpJNI() {}

    public static native long newModbusContext(String ipAddress, int port);
}
