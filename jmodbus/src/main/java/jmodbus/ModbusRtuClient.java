package jmodbus;

public class ModbusRtuClient extends ModbusClient {

    public ModbusRtuClient(long contextPtr) {
        super(contextPtr);
    }

    public void setDelayMicroseconds(int delay) {
        ModbusRtuJNI.setDelayMicroseconds(delay);
    }

    public int getDelayMicroseconds() {
        return ModbusRtuJNI.getDelayMicroseconds();
    }
}
