# jmodbus

![maven central](https://img.shields.io/maven-central/v/com.github.tomtzook/jmodbus)

A java integration for [libmodbus](https://github.com/stephane/libmodbus/)
Basically using JNI wrappers to supply _libmodbus_ functionality, while providing some integrations
for java structures and such.

Only supporting _TCP/Serial-RTU clients and TCP server_ for now.

## Usage

_jmodbus_ is published to _maven central_. For _gradle_, use
```groovy
// for the java API
implementation group: 'com.github.tomtzook', name: 'jmodbus', version: version
// for the JNI natives
implementation group: 'com.github.tomtzook', name: 'jmodbus-jni', version: version, classifier: platform
```

The `classifier` specifies the platform which is used, can be one of:
- `linux-aarch64`
- `linux-amd64`
- `linux-gnueabihf-arm`
- `windows-x86_x64`

Load the natives from the _jni_ dependency. Can be done easily with [_castle_](https://github.com/tomtzook/Castle):
```java
Natives.newLoader()
        .load("modbus_jni");
```

_libmodbus_ should be already installed on the system.

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
final int maxBacklogSize = 2;
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
        maxBacklogSize,
        registers
)) {
    
    // buffer for requests
    ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
    
    // loop for handling clients
    while (true) {
        ServerDataUpdate update = server.waitForNewData();
        try {
            switch(update.getType()) {
                case NEW_CLIENT:
                    // new client wants to connect
                    update.accept();
                    break;
                case NEW_DATA:
                    // a client sent a request
                    TcpRequest request = update.readClientRequest(buffer);
                    // can access request info if wanted
                    // reply the client with data in Registers
                    request.reply();
                    break;
            }
        } catch(ModbusIoException e) {
            // error with the client
            update.closeCurrentClient();
        }
    }
}
```

### Using Server Registers

The `Registers` class describes 4 data block, matching the standard data types in _modbus_.
Each data block is either a `BitDataBlock` for bit sized data types or `WordDataBlock` for word sized types.

Per _modbus_'s specs, the data blocks store data in _big endian_ order. 

These data blocks contain the values that are to be returned to the clients on a request. Modify these regularly, or
when a request is received, to update the data returned to the client. Query this regularly to see data
set by the clients.
