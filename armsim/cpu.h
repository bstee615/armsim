#ifndef CPU_H
#define CPU_H

#include "memory.h"

class CPU
{
    Memory ram;
    Memory programCounter;

public:
    CPU();

    // Reads a word from the RAM address specified by the value of the simulated Program Counter register.
    word fetch();
    // Does nothing for now.
    void decode(word w);
    // Waits for 0.25sec.
    void execute();
};

#endif // CPU_H
