package jmodbus.server;

public enum RegisterSize {
    BIT(1),
    WORD(2);

    private final int mByteSize;

    RegisterSize(int byteSize) {
        mByteSize = byteSize;
    }

    public int byteSize() {
        return mByteSize;
    }
}
