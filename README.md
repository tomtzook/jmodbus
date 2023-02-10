# jmodbus

![maven central](https://img.shields.io/maven-central/v/com.github.tomtzook/jmodbus)

A java integration for [libmodbus](https://github.com/stephane/libmodbus/)
Basically using JNI wrappers to supply _libmodbus_ functionality, while providing some integrations
for java structures and such.

Only supporting _TCP/Serial-RTU clients and TCP server_ for now.

## Usage

### Using a TCP client

```java
try (ModbusClient client = Modbus.newTcpClient("127.0.0.1", 1524)) {
    client.connect();
    
    // read an int made out of two registers
    ByteBuffer buffer = ByteBuffer.allocate(4);
    client.readHoldingRegisters(0x0, 2, buffer);
    
    int value = buffer.order(ByteOrder.BIG_ENDIAN).asIntBuffer().get(0);
}
```

### Using an RTU client

```java
try (ModbusClient client = Modbus.newRtuClient(
        "/dev/ttyUSB0", 
        9600, 
        Parity.EVEN, 
        Databit.BYTESIZE_8, 
        Stopbit.STOPBIT_1, 
        SerialMode.RS485)) {
    client.connect();
    
    // read an int made out of two registers
    ByteBuffer buffer = ByteBuffer.allocate(4);
    client.readHoldingRegisters(0x0, 2, buffer);
    
    int value = buffer.order(ByteOrder.BIG_ENDIAN).asIntBuffer().get(0);
}
```

### Using a TCP server

```java
final int maxAllowedConnectedClients = 2;
final int numberOfDiscreteBits = 2;
final int numberOfCoils = 2;
final int numberOfInputRegisters = 2;
final int numberOfHoldingRegisters = 2;

// holds data blocks which are returned upon client requests
// update the data here to update the data sent to clients
Registers registers = new Registers(
        numberOfDiscreteBits,
        numberOfCoils,
        numberOfInputRegisters,
        numberOfHoldingRegisters
);

try (ModbusTcpServer server = Modbus.newTcpServer(
        "0.0.0.0", 5000,
        maxAllowedConnectedClients,
        registers
)) {
    
    // buffer for requests
    ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
    
    // loop for handling clients
    while (true) {
        try {
            PendingDataType type = server.waitForNewData();
            switch(type) {
                case NEW_CLIENT:
                    // new client wants to connect
                    server.accept();
                    break;
                case NEW_DATA:
                    // a client sent a request
                    int readCount = server.readClientRequest(buffer);
                    // reply the client with data in Registers
                    server.replyClient(buffer, readCount);
                    break;
            }
        } catch(ModbusIoException e) {
            // error with the client
            server.closeCurrentClient();
        }
    }
}
```
