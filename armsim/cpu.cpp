#include "cpu.h"
#include <chrono>
#include <thread>

CPU::CPU(Memory *ram): _ram(ram), registers(Memory(NUM_REGISTER_BYTES))
{
    qDebug() << "CPU:" << "Initialized with" << _ram->getSize() << "bytes of RAM and" << registers.getSize() << "bytes of register memory.";
}

word CPU::fetch()
{
    auto addressToFetch = registers.ReadWord(PC_OFFSET);
    registers.WriteWord(PC_OFFSET, addressToFetch + 4);
    return _ram->ReadWord(addressToFetch);
}

void CPU::decode(word w)
{

}

void CPU::execute()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
}

byte CPU::getNZSF()
{
    return registers.ReadByte(NZCF_OFFSET) & 0x0F; // Mask it just to make sure
}

word CPU::getGeneralRegister(unsigned int index)
{
    if (index > 11) throw InvalidRegisterIndexException();
    return registers.ReadWord(R0_OFFSET + index*4);
}
