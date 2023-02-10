package jmodbus.rtu;

public enum SerialMode {
    RS232(0),
    RS485(1)
    ;

    private final int mIntValue;

    SerialMode(int intValue) {
        mIntValue = intValue;
    }

    public int intValue() {
        return mIntValue;
    }
}
