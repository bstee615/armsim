#include "cpu.h"
#include <chrono>
#include <thread>
#include "dataprocessinginstruction.h"
#include "instructionfactory.h"

CPU::CPU(Memory *ram): _ram(ram), registers(new Memory(NUM_REGISTER_BYTES))
{
    qDebug() << "CPU:" << "Initialized with" << _ram->getSize() << "bytes of RAM and" << registers->getSize() << "bytes of register memory.";
}

word CPU::fetch()
{
    auto addressToFetch = registers->ReadWord(PC_OFFSET);
    return _ram->ReadWord(addressToFetch);
}

void CPU::incrementPC()
{
    registers->WriteWord(PC_OFFSET, registers->ReadWord(PC_OFFSET) + 4);
}

Instruction *CPU::decode(word w)
{
    return InstructionFactory::getDecodedInstruction(w, _ram, registers);
}

void CPU::execute(Instruction *instr)
{
    // Instructions cannot have a reference to CPU because of a circular dependency.
    //  To implement SWI, the CPU will have to cast an Instruction* to a SoftwareInterruptInstruction*
    //  to check whether instr is a SoftwareInterruptInstruction.

    if (instr != nullptr) {
        instr->execute();
    }
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
    return registers->TestFlag(CPSR_OFFSET, whichFlag);
}

void checkForInvalidRegister(unsigned int index)
{
    if (index > 15) throw InvalidRegisterIndexException();
}

word CPU::getGeneralRegister(unsigned int index)
{
    checkForInvalidRegister(index);
    return registers->ReadWord(R0_OFFSET + index*4);
}

void CPU::setNZCFFlag(NZCFFlag whichFlag, bool val)
{
    registers->SetFlag(CPSR_OFFSET, whichFlag, val);
}

void CPU::setGeneralRegister(unsigned int index, word w)
{
    checkForInvalidRegister(index);
    return registers->WriteWord(R0_OFFSET + index*4, w);
}
