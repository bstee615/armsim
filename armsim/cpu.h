#ifndef CPU_H
#define CPU_H

#include "memory.h"

#define R0_OFFSET 0
#define R1_OFFSET 4
#define R2_OFFSET 8
#define R3_OFFSET 12
#define R4_OFFSET 16
#define R5_OFFSET 20
#define R6_OFFSET 24
#define R7_OFFSET 28
#define R8_OFFSET 32
#define R9_OFFSET 36
#define R10_OFFSET 40
#define R11_OFFSET 44
#define IP_OFFSET 48
#define SP_OFFSET 52
#define LR_OFFSET 56
#define PC_OFFSET 60
#define CPSR_OFFSET 64
#define NZCF_OFFSET 68

#define NUM_REGISTER_BYTES 72

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

    Memory *getRAM() { return _ram; }
    address getProgramCounter() { return registers.ReadWord(PC_OFFSET); }
    void setProgramCounter(address addr) { registers.WriteWord(PC_OFFSET, addr); }
};

#endif // CPU_H
