package jmodbus;

public enum Stopbit {
    STOPBIT_1(1),
    STOPBIT_2(2)
    ;

    private final int mIntValue;

    Stopbit(int intValue) {
        mIntValue = intValue;
    }

    public int intValue() {
        return mIntValue;
    }
}
