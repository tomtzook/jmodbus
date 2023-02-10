
#include "modbus_registers.h"


DEFINE_OBJECT_TYPE(ByteBuffer, "java/nio/ByteBuffer")
DEFINE_OBJECT_TYPE(Registers, "jmodbus/server/Registers")
DEFINE_OBJECT_TYPE(DataBlock, "jmodbus/server/DataBlock")
DEFINE_OBJECT_TYPE(BitDataBlock, "jmodbus/server/BitDataBlock")
DEFINE_OBJECT_TYPE(WordDataBlock, "jmodbus/server/WordDataBlock")

template<typename T>
static inline void fill_mapping(
        JNIEnv* _env,
        jnikit::Object<DataBlock>& regs,
        int& nb,
        int& start,
        T*& tab) {
    auto jstart_address = regs.callMethod<jnikit::types::Int>("getStartAddress");
    auto jsize = regs.callMethod<jnikit::types::Int>("getSize");
    auto jbuffer = regs.callMethod<ByteBuffer>("getBuffer");

    nb = jsize;
    start = jstart_address;
    tab = reinterpret_cast<T*>(_env->GetDirectBufferAddress(jbuffer));
}

modbus_mapping_t mapping_from_java(JNIEnv* _env, jobject _registers) {
    jnikit::Env env(_env);

    auto registers = env.wrap<Registers>(_registers);
    auto discreteBlock = env.wrap<DataBlock>(registers.callMethod<BitDataBlock>("getDiscreteBits"));
    auto coils = env.wrap<DataBlock>(registers.callMethod<BitDataBlock>("getCoils"));
    auto inputRegisters = env.wrap<DataBlock>(registers.callMethod<WordDataBlock>("getInputRegisters"));
    auto holdingRegisters = env.wrap<DataBlock>(registers.callMethod<WordDataBlock>("getHoldingRegisters"));

    modbus_mapping_t mapping;
    fill_mapping(
            _env,
            discreteBlock,
            mapping.nb_input_bits,
            mapping.start_input_bits,
            mapping.tab_input_bits);
    fill_mapping(
            _env,
            coils,
            mapping.nb_bits,
            mapping.start_bits,
            mapping.tab_bits);
    fill_mapping(
            _env,
            inputRegisters,
            mapping.nb_input_registers,
            mapping.start_input_registers,
            mapping.tab_input_registers);
    fill_mapping(
            _env,
            holdingRegisters,
            mapping.nb_registers,
            mapping.start_registers,
            mapping.tab_registers);

    return mapping;
}
