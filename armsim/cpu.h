#ifndef CPU_H
#define CPU_H

#include "instructions/nzcf.h"
#include "memory.h"
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
    Memory *registers;

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
    Memory *getRegisters() { return registers; }

    address getProgramCounter() { return registers->ReadWord(PC_OFFSET); }
    void setProgramCounter(address addr) { registers->WriteWord(PC_OFFSET, addr); }
    byte getNZCF();
    bool getNZCF(NZCFFlag whichFlag);
    word getGeneralRegister(unsigned int index);
    void setNZCFFlag(NZCFFlag whichFlag, bool val);
    void setGeneralRegister(unsigned int index, word w);
};

#endif // CPU_H
