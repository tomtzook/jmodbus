package jmodbus.server;

public class BitDataBlock extends DataBlock {

    public BitDataBlock(int startAddress, int size) {
        super(startAddress, size, RegisterSize.BIT);
    }

    public void put(int address, boolean value) {
        getBuffer().put(offset(address), (byte) (value ? 1 : 0));
    }

    public boolean get(int address) {
        return getBuffer().get(offset(address)) != 0;
    }
}
