#ifndef CPU_H
#define CPU_H

#include "memory.h"
#include "loader.h"

#define PC_OFFSET 0

class CPU
{
    Memory &_ram;
    Memory registers;

public:
    CPU(Memory &ram);

    // Reads a word from the RAM address specified by the value of the simulated Program Counter register.
    word fetch();
    // Does nothing for now.
    void decode(word w);
    // Waits for 0.25sec.
    void execute();
};

#endif // CPU_H
