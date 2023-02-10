package jmodbus.rtu;

public class ModbusRtuJNI {

    private ModbusRtuJNI() {}

    public static native long newModbusContext(
            String port,
            int buadRate,
            Parity parity,
            Databit databit,
            Stopbit stopbit,
            SerialMode serialMode);

    public static native int getDelayMicroseconds();
    public static native void setDelayMicroseconds(int microseconds);
}
