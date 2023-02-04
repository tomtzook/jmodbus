package jmodbus;

public class SlaveOrServerBusyException extends ModbusException {

    public SlaveOrServerBusyException(String message) {
        super(message);
    }
}
