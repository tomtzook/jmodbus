package jmodbus;

public class TimeValue {

    private final int mSeconds;
    private final int mMicroseconds;

    public TimeValue(int seconds, int microseconds) {
        mSeconds = seconds;
        mMicroseconds = microseconds;
    }

    public int getSeconds() {
        return mSeconds;
    }

    public int getMicroseconds() {
        return mMicroseconds;
    }
}
