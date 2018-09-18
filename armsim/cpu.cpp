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

byte CPU::getNZCF()
{
    return (unsigned int)getNZCF(NZCFFlag::Negative) << 3 |
           (unsigned int)getNZCF(NZCFFlag::Zero) << 2 |
           (unsigned int)getNZCF(NZCFFlag::Carry) << 1 |
           (unsigned int)getNZCF(NZCFFlag::Overflow);
}

bool CPU::getNZCF(NZCFFlag whichFlag)
{
    return registers.TestFlag(CPSR_OFFSET, whichFlag);
}

void checkForInvalidRegister(unsigned int index)
{
    if (index > 15) throw InvalidRegisterIndexException();
}

word CPU::getGeneralRegister(unsigned int index)
{
    checkForInvalidRegister(index);
    return registers.ReadWord(R0_OFFSET + index*4);
}

void CPU::setNZCFFlag(NZCFFlag whichFlag, bool val)
{
    registers.SetFlag(CPSR_OFFSET, whichFlag, val);
}

void CPU::setGeneralRegister(unsigned int index, word w)
{
    checkForInvalidRegister(index);
    return registers.WriteWord(R0_OFFSET + index*4, w);
}
