package jmodbus.server;

public class Registers {

    private final BitDataBlock mDiscreteBits;
    private final BitDataBlock mCoils;
    private final WordDataBlock mInputRegisters;
    private final WordDataBlock mHoldingRegisters;

    public Registers(BitDataBlock discreteBits,
                     BitDataBlock coils,
                     WordDataBlock inputRegisters,
                     WordDataBlock holdingRegisters) {
        mDiscreteBits = discreteBits;
        mCoils = coils;
        mInputRegisters = inputRegisters;
        mHoldingRegisters = holdingRegisters;
    }

    public Registers(int discreteStartAddress, int discreteCount,
                     int coilsStartAddress, int coilsCount,
                     int inputRegistersStartAddress, int inputRegistersCount,
                     int holdingRegistersStartAddress, int holdingRegistersCount) {
        this(
                new BitDataBlock(discreteStartAddress, discreteCount),
                new BitDataBlock(coilsStartAddress, coilsCount),
                new WordDataBlock(inputRegistersStartAddress, inputRegistersCount),
                new WordDataBlock(holdingRegistersStartAddress, holdingRegistersCount)
        );
    }

    public Registers(int discreteCount,
                     int coilsCount,
                     int inputRegistersCount,
                     int holdingRegistersCount) {
        this(
                0, discreteCount,
                0, coilsCount,
                0, inputRegistersCount,
                0, holdingRegistersCount
        );
    }

    public BitDataBlock getDiscreteBits() {
        return mDiscreteBits;
    }

    public BitDataBlock getCoils() {
        return mCoils;
    }

    public WordDataBlock getInputRegisters() {
        return mInputRegisters;
    }

    public WordDataBlock getHoldingRegisters() {
        return mHoldingRegisters;
    }
}
