#ifndef CPU_H
#define CPU_H

#include "memory.h"

#define R0_OFFSET 0
#define IP_OFFSET 48
#define SP_OFFSET 52
#define LR_OFFSET 56
#define PC_OFFSET 60
#define CPSR_OFFSET 64
#define NZCF_OFFSET 68

#define NUM_REGISTER_BYTES 72

// To be thrown when GetRegister recieves an index that's greater than r11,
//  because then the index would rather throw an OutOfBoundsException (unclear for debugging)
//  or would pull from another register.
//  The only exception is maybe I should enable up to r13, since r13 is the stack pointer.
// I chose to make a new exception for this case rather than use OutOfBoundsException,
//  defined in memory.h, to ease debugging, so that I know for sure why it's happening.
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
    Memory registers;

public:
    CPU() {}
    CPU(Memory *ram);

    // Reads a word from the RAM address specified by the value of the simulated Program Counter register.
    word fetch();
    // Does nothing for now.
    void decode(word w);
    // Waits for 0.25sec.
    void execute();

    address getChecksum() { return _ram->Checksum(); }
    Memory *getRAM() { return _ram; }
    address getProgramCounter() { return registers.ReadWord(PC_OFFSET); }
    void setProgramCounter(address addr) { registers.WriteWord(PC_OFFSET, addr); }

    byte getNZSF();
    word getGeneralRegister(unsigned int index);
};

#endif // CPU_H
