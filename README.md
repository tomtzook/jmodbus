# jmodbus

A java integration for [libmodbus](https://github.com/stephane/libmodbus/)
Basically using JNI wrappers to supply _libmodbus_ functionality, while providing some integrations
for java structures and such.

Only supporting _TCP clients_ for now.

## Creating a TCP client

```java
try (ModbusClient client = Modbus.newTcpClient("127.0.0.1", 1524)) {
    client.connect();
    
    // read an int made out of two registers
    ByteBuffer buffer = ByteBuffer.allocate(4);
    client.readHoldingRegisters(0x0, 2, buffer);
    
    int value = buffer.order(ByteOrder.BIG_ENDIAN).asIntBuffer().get(0);
}
```