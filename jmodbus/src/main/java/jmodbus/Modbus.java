package jmodbus;

public class Modbus {

    private Modbus() {}

    public static ModbusClient newTcpClient(String ipAddress, int port) {
        long contextPtr = ModbusTcpJNI.newModbusContext(ipAddress, port);
        return new ModbusClient(contextPtr);
    }
}
