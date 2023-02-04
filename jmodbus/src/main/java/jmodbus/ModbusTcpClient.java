package jmodbus;

public class ModbusTcpClient extends ModbusClient {

    public ModbusTcpClient(String ipAddress, int port) {
        super(ModbusTcpJNI.newModbusContext(ipAddress, port));
    }
}
