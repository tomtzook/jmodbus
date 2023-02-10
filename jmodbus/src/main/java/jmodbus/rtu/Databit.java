package jmodbus.rtu;

public enum Databit {
    BYTESIZE_5(5),
    BYTESIZE_6(6),
    BYTESIZE_7(7),
    BYTESIZE_8(7);

    private final int mIntValue;

    Databit(int intValue) {
        mIntValue = intValue;
    }

    public int intValue() {
        return mIntValue;
    }
}
