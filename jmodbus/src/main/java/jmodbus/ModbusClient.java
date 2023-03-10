package jmodbus;

import java.nio.Buffer;
import java.nio.ByteBuffer;

public class ModbusClient extends ModbusContextBase {

    protected ModbusClient(long contextPtr) {
        super(contextPtr);
    }

    public void readDiscreteInputs(int address, int count, byte[] buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count, buffer.length);

            ModbusJNI.readDiscreteInputs4(mContextPtr, address, count, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void readDiscreteInputs(int address, int count, ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyBufferUsableForRead(buffer, count);

            if (buffer.isDirect()) {
                ModbusJNI.readDiscreteInputs3(mContextPtr, address, count, buffer);
            } else if (buffer.hasArray()) {
                ModbusJNI.readDiscreteInputs4(mContextPtr, address, count, buffer.array());
            } else {
                throw new UnsupportedOperationException("buffer which is proxy to another cannot be used");
            }
        } finally {
            mLock.unlock();
        }
    }

    public long readDiscreteInputsAsBitField(int address, int count) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyCountLimitedToLongBits(count);

            return ModbusJNI.readDiscreteInputs2(mContextPtr, address, count);
        } finally {
            mLock.unlock();
        }
    }

    public void readCoils(int address, int count, byte[] buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count, buffer.length);

            ModbusJNI.readCoils4(mContextPtr, address, count, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void readCoils(int address, int count, ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyBufferUsableForRead(buffer, count);

            if (buffer.isDirect()) {
                ModbusJNI.readCoils3(mContextPtr, address, count, buffer);
            } else if (buffer.hasArray()) {
                ModbusJNI.readCoils4(mContextPtr, address, count, buffer.array());
            } else {
                throw new UnsupportedOperationException("buffer which is proxy to another cannot be used");
            }
        } finally {
            mLock.unlock();
        }
    }

    public long readCoilsAsBitField(int address, int count) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyCountLimitedToLongBits(count);

            return ModbusJNI.readCoils2(mContextPtr, address, count);
        } finally {
            mLock.unlock();
        }
    }

    public void readInputRegisters(int address, int count, short[] buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count, buffer.length);

            ModbusJNI.readInputRegisters(mContextPtr, address, count, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void readInputRegisters(int address, int count, byte[] buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count * 2, buffer.length);

            ModbusJNI.readInputRegisters3(mContextPtr, address, count, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void readInputRegisters(int address, int count, ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyBufferUsableForRead(buffer, count * 2); // short = 2 * byte

            if (buffer.isDirect()) {
                ModbusJNI.readInputRegisters2(mContextPtr, address, count, buffer);
            } else if (buffer.hasArray()) {
                ModbusJNI.readInputRegisters3(mContextPtr, address, count, buffer.array());
            } else {
                throw new UnsupportedOperationException("buffer which is proxy to another cannot be used");
            }
        } finally {
            mLock.unlock();
        }
    }

    public void readHoldingRegisters(int address, int count, short[] buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count, buffer.length);

            ModbusJNI.readHoldingRegisters(mContextPtr, address, count, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void readHoldingRegisters(int address, int count, byte[] buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count * 2, buffer.length);

            ModbusJNI.readHoldingRegisters3(mContextPtr, address, count, buffer);
        } finally {
            mLock.unlock();
        }
    }

    public void readHoldingRegisters(int address, int count, ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyBufferUsableForRead(buffer, count * 2);

            if (buffer.isDirect()) {
                ModbusJNI.readHoldingRegisters2(mContextPtr, address, count, buffer);
            } else if (buffer.hasArray()) {
                ModbusJNI.readHoldingRegisters3(mContextPtr, address, count, buffer.array());
            } else {
                throw new UnsupportedOperationException("buffer which is proxy to another cannot be used");
            }
        } finally {
            mLock.unlock();
        }
    }

    public void writeCoil(int address, byte value) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.writeCoil2(mContextPtr, address, value);
        } finally {
            mLock.unlock();
        }
    }

    public void writeCoils(int address, int count, byte[] values) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count, values.length);

            ModbusJNI.writeCoils3(mContextPtr, address, count, values);
        } finally {
            mLock.unlock();
        }
    }

    public void writeCoils(int address, int count, ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyBufferUsableForWrite(buffer, count);

            if (buffer.isDirect()) {
                ModbusJNI.writeCoils4(mContextPtr, address, count, buffer);
            } else if (buffer.hasArray()) {
                ModbusJNI.writeCoils3(mContextPtr, address, count, buffer.array());
            } else {
                throw new UnsupportedOperationException("buffer which is proxy to another cannot be used");
            }
        } finally {
            mLock.unlock();
        }
    }

    public void writeCoilsFromBitField(int address, int count, long values) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);

            ModbusJNI.writeCoils2(mContextPtr, address, count, values);
        } finally {
            mLock.unlock();
        }
    }

    public void writeHoldingRegister(int address, short value) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.writeHoldingRegister(mContextPtr, address, value);
        } finally {
            mLock.unlock();
        }
    }

    public void writeHoldingRegisters(int address, int count, short[] values) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count, values.length);

            ModbusJNI.writeHoldingRegisters(mContextPtr, address, count, values);
        } finally {
            mLock.unlock();
        }
    }

    public void writeHoldingRegisters(int address, int count, byte[] values) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyArrayContainsEnoughForCount(count * 2, values.length);

            ModbusJNI.writeHoldingRegisters3(mContextPtr, address, count, values);
        } finally {
            mLock.unlock();
        }
    }

    public void writeHoldingRegisters(int address, int count, ByteBuffer buffer) {
        mLock.lock();
        try {
            verifyNotClosed();
            verifyValidCount(count);
            verifyBufferUsableForWrite(buffer, count * 2);

            if (buffer.isDirect()) {
                ModbusJNI.writeHoldingRegisters2(mContextPtr, address, count, buffer);
            } else if (buffer.hasArray()) {
                ModbusJNI.writeHoldingRegisters3(mContextPtr, address, count, buffer.array());
            } else {
                throw new UnsupportedOperationException("buffer which is proxy to another cannot be used");
            }
        } finally {
            mLock.unlock();
        }
    }

    public void flush() {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.flush(mContextPtr);
        } finally {
            mLock.unlock();
        }
    }

    public void connect() {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.connect(mContextPtr);
        } finally {
            mLock.unlock();
        }
    }

    public void setDebugEnabled(boolean isEnabled) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.setDebug(mContextPtr, isEnabled);
        } finally {
            mLock.unlock();
        }
    }

    public void setSlave(int slave) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.setSlave(mContextPtr, slave);
        } finally {
            mLock.unlock();
        }
    }

    public int getSlave() {
        mLock.lock();
        try {
            verifyNotClosed();

            return ModbusJNI.getSlave(mContextPtr);
        } finally {
            mLock.unlock();
        }
    }

    public void setResponseTimeout(TimeValue timeout) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.setResponseTimeout(mContextPtr, timeout);
        } finally {
            mLock.unlock();
        }
    }

    public TimeValue getResponseTimeout() {
        mLock.lock();
        try {
            verifyNotClosed();

            return ModbusJNI.getResponseTimeout(mContextPtr);
        } finally {
            mLock.unlock();
        }
    }

    public void setByteTimeout(TimeValue timeout) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.setByteTimeout(mContextPtr, timeout);
        } finally {
            mLock.unlock();
        }
    }

    public TimeValue getByteTimeout() {
        mLock.lock();
        try {
            verifyNotClosed();

            return ModbusJNI.getByteTimeout(mContextPtr);
        } finally {
            mLock.unlock();
        }
    }

    public void setIndicationTimeout(TimeValue timeout) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusJNI.setIndicationTimeout(mContextPtr, timeout);
        } finally {
            mLock.unlock();
        }
    }

    public TimeValue getIndicationTimeout() {
        mLock.lock();
        try {
            verifyNotClosed();

            return ModbusJNI.getIndicationTimeout(mContextPtr);
        } finally {
            mLock.unlock();
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

    private void verifyBufferUsableForRead(Buffer buffer, int neededSize) {
        if (buffer.isReadOnly()) {
            throw new IllegalArgumentException("buffer is read-only");
        }
        if (buffer.capacity() < neededSize) {
            throw new IllegalArgumentException("buffer is too small");
        }
    }

    private void verifyBufferUsableForWrite(Buffer buffer, int wantedSize) {
        if (buffer.capacity() < wantedSize) {
            throw new IllegalArgumentException("buffer is too small");
        }
    }
}
