package jmodbus;

import jmodbus.rtu.Databit;
import jmodbus.rtu.ModbusRtuClient;
import jmodbus.rtu.ModbusRtuJNI;
import jmodbus.rtu.Parity;
import jmodbus.rtu.SerialMode;
import jmodbus.rtu.Stopbit;
import jmodbus.server.Registers;
import jmodbus.tcp.ModbusTcpJNI;
import jmodbus.tcp.server.ModbusTcpServer;

public class Modbus {

    private Modbus() {}

    public static final String JNI_LIBNAME = "modbus_jni";

    public static ModbusClient newTcpClient(String ipAddress, int port) {
        long contextPtr = ModbusTcpJNI.newModbusContext(ipAddress, port);
        return new ModbusClient(contextPtr);
    }

    public static ModbusTcpServer newTcpServer(String ipAddress, int port, int backlogSize, Registers registers) {
        long contextPtr = ModbusTcpJNI.newModbusContext(ipAddress, port);
        return new ModbusTcpServer(contextPtr, backlogSize, registers);
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
