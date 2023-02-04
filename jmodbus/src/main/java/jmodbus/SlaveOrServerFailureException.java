package jmodbus;

public class SlaveOrServerFailureException extends ModbusException {

    public SlaveOrServerFailureException(String message) {
        super(message);
    }
}
