package jmodbus;

public enum Parity {
    ODD('O'),
    EVEN('E'),
    NONE('N')
    ;

    private final char mCharValue;

    Parity(char charValue) {
        mCharValue = charValue;
    }

    public char charValue() {
        return mCharValue;
    }
}
