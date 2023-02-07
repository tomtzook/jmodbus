package jmodbus;

public class Modbus {

    private Modbus() {}

    public static ModbusClient newTcpClient(String ipAddress, int port) {
        long contextPtr = ModbusTcpJNI.newModbusContext(ipAddress, port);
        return new ModbusClient(contextPtr);
    }

    public static ModbusRtuClient newRtuClient(String port,
                                            int buadRate,
                                            Parity parity,
                                            Databit databit,
                                            Stopbit stopbit,
                                            SerialMode serialMode) {
        long contextPtr = ModbusRtuJNI.newModbusContext(
                port, buadRate, parity, databit, stopbit, serialMode);
        return new ModbusRtuClient(contextPtr);
    }
}
