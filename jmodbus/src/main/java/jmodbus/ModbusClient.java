package jmodbus;

import java.io.Closeable;
import java.io.IOException;

public class ModbusClient implements Closeable {

    protected long mContextPtr;

    protected ModbusClient(long contextPtr) {
        mContextPtr = contextPtr;
    }

    public boolean[] readCoils(int address, int count) {
        assert count >= 1;
        assertNotClosed();
        return ModbusJNI.readCoils(mContextPtr, address, count);
    }

    public boolean[] readDiscreteInputs(int address, int count) {
        assert count >= 1;
        assertNotClosed();
        return ModbusJNI.readDiscreteInputs(mContextPtr, address, count);
    }

    public short[] readInputRegisters(int address, int count) {
        assert count >= 1;
        assertNotClosed();
        return ModbusJNI.readInputRegisters(mContextPtr, address, count);
    }

    public short[] readHoldingRegisters(int address, int count) {
        assert count >= 1;
        assertNotClosed();
        return ModbusJNI.readHoldingRegisters(mContextPtr, address, count);
    }

    public void writeCoil(int address, boolean value) {
        assertNotClosed();
        ModbusJNI.writeCoil(mContextPtr, address, value);
    }

    public void writeCoils(int address, int count, boolean[] values) {
        assert count >= 1;
        assertNotClosed();
        ModbusJNI.writeCoils(mContextPtr, address, count, values);
    }

    public void writeHoldingRegister(int address, short value) {
        assertNotClosed();
        ModbusJNI.writeHoldingRegister(mContextPtr, address, value);
    }

    public void writeHoldingRegisters(int address, int count, short[] values) {
        assert count >= 1;
        assertNotClosed();
        ModbusJNI.writeHoldingRegisters(mContextPtr, address, count, values);
    }

    public void connect() {
        ModbusJNI.connect(mContextPtr);
    }

    public void setDebugEnabled(boolean isEnabled) {
        ModbusJNI.setDebug(mContextPtr, isEnabled);
    }

    public void setSlave(int slave) {
        ModbusJNI.setSlave(mContextPtr, slave);
    }

    @Override
    public void close() throws IOException {
        ModbusJNI.close(mContextPtr);
        ModbusJNI.free(mContextPtr);
        mContextPtr = 0;
    }

    private void assertNotClosed() {
        if (mContextPtr == 0) {
            throw new IllegalStateException("already closed");
        }
    }
}
