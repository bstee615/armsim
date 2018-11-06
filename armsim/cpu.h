#ifndef CPU_H
#define CPU_H

#include "registermemory.h"
#include "instructions/instruction.h"

struct InvalidRegisterIndexException : public std::exception
{
    const char * what () const noexcept
    {
        return "Invalid register index";
    }
};

class CPU
{
    Memory *_ram;
    RegisterMemory *registers;

public:
    CPU() {}
    CPU(Memory *ram);

    // Reads a word from the RAM address specified by the value of the simulated Program Counter register.
    word fetch();
    void incrementPC();
    // Does nothing for now.
    Instruction *decode(word w);
    // Waits for 0.25sec.
    void execute(Instruction *instr);
    // Clears memory, GPR's, and NZCF flags.
    void reset();

    address getChecksum() { return _ram->Checksum(); }
    Memory *getRAM() { return _ram; }
    RegisterMemory *getRegisters() { return registers; }

    address getProgramCounter() { return registers->getRegisterValue(15); }
    void setProgramCounter(address addr) { registers->setRegisterValue(15, addr); }
    byte getNZCF();
    word getGeneralRegister(unsigned int index);
    void setNZCFFlag(NZCFFlag whichFlag, bool val);
    void setGeneralRegister(unsigned int index, word w);
};

#endif // CPU_H
