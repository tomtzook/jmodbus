package jmodbus.rtu;

import jmodbus.ModbusClient;

public class ModbusRtuClient extends ModbusClient {

    public ModbusRtuClient(long contextPtr) {
        super(contextPtr);
    }

    public void setDelayMicroseconds(int delay) {
        mLock.lock();
        try {
            verifyNotClosed();

            ModbusRtuJNI.setDelayMicroseconds(delay);
        } finally {
            mLock.unlock();
        }
    }

    public int getDelayMicroseconds() {
        mLock.lock();
        try {
            verifyNotClosed();

            return ModbusRtuJNI.getDelayMicroseconds();
        } finally {
            mLock.unlock();
        }
    }
}
