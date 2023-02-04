package jmodbus;

import java.io.Closeable;
import java.nio.Buffer;
import java.nio.ByteBuffer;

public class ModbusClient implements Closeable {

    protected final long mContextPtr;
    private boolean mIsClosed;

    protected ModbusClient(long contextPtr) {
        mContextPtr = contextPtr;
        mIsClosed = false;
    }

    public boolean[] readCoils(int address, int count) {
        verifyNotClosed();
        verifyValidCount(count);

        return ModbusJNI.readCoils(mContextPtr, address, count);
    }

    public void readCoils(int address, int count, ByteBuffer buffer) {
        verifyNotClosed();
        verifyValidCount(count);
        verifyBufferUseable(buffer, count);

        ModbusJNI.readCoils3(mContextPtr, address, count, buffer);
    }

    public long readCoilsToBitField(int address, int count) {
        verifyNotClosed();
        verifyValidCount(count);
        verifyCountLimitedToLongBits(count);

        return ModbusJNI.readCoils2(mContextPtr, address, count);
    }

    public boolean[] readDiscreteInputs(int address, int count) {
        verifyNotClosed();
        verifyValidCount(count);

        return ModbusJNI.readDiscreteInputs(mContextPtr, address, count);
    }

    public void readDiscreteInputs(int address, int count, ByteBuffer buffer) {
        verifyNotClosed();
        verifyValidCount(count);
        verifyBufferUseable(buffer, count);

        ModbusJNI.readDiscreteInputs3(mContextPtr, address, count, buffer);
    }

    public long readDiscreteInputsToBitField(int address, int count) {
        verifyNotClosed();
        verifyValidCount(count);
        verifyCountLimitedToLongBits(count);

        return ModbusJNI.readDiscreteInputs2(mContextPtr, address, count);
    }

    public short[] readInputRegisters(int address, int count) {
        verifyNotClosed();
        verifyValidCount(count);

        return ModbusJNI.readInputRegisters(mContextPtr, address, count);
    }

    public short[] readHoldingRegisters(int address, int count) {
        verifyNotClosed();
        verifyValidCount(count);

        return ModbusJNI.readHoldingRegisters(mContextPtr, address, count);
    }

    public void writeCoil(int address, boolean value) {
        verifyNotClosed();

        ModbusJNI.writeCoil(mContextPtr, address, value);
    }

    public void writeCoils(int address, int count, boolean[] values) {
        verifyNotClosed();
        verifyValidCount(count);
        verifyArrayContainsEnoughForCount(count, values.length);

        ModbusJNI.writeCoils(mContextPtr, address, count, values);
    }

    public void writeCoilsFromBitField(int address, int count, long values) {
        verifyNotClosed();
        verifyValidCount(count);

        ModbusJNI.writeCoils2(mContextPtr, address, count, values);
    }

    public void writeHoldingRegister(int address, short value) {
        verifyNotClosed();

        ModbusJNI.writeHoldingRegister(mContextPtr, address, value);
    }

    public void writeHoldingRegisters(int address, int count, short[] values) {
        verifyNotClosed();
        verifyValidCount(count);
        verifyArrayContainsEnoughForCount(count, values.length);

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
    public void close() {
        ModbusJNI.close(mContextPtr);
        ModbusJNI.free(mContextPtr);
        mIsClosed = true;
    }

    private void verifyNotClosed() {
        if (mIsClosed) {
            throw new IllegalStateException("already closed");
        }
    }

    private void verifyValidCount(int count) {
        if (count <= 0) {
            throw new IllegalArgumentException("count must be positive");
        }
    }

    private void verifyCountLimitedToLongBits(int count) {
        if (count > 64) {
            throw new IllegalArgumentException("count cannot exceed size of long");
        }
    }

    private void verifyArrayContainsEnoughForCount(int count, int arrayLength) {
        if (arrayLength < count) {
            throw new IllegalArgumentException("array too small for requested count");
        }
    }

    private void verifyBufferUseable(Buffer buffer, int neededSize) {
        if (!buffer.isDirect()) {
            throw new IllegalArgumentException("only direct buffers are supported");
        }
        if (buffer.isReadOnly()) {
            throw new IllegalArgumentException("buffer is read-only");
        }

        if (buffer.capacity() < neededSize) {
            throw new IllegalArgumentException("buffer is too small");
        }
    }
}
