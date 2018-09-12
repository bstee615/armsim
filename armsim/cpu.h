#ifndef CPU_H
#define CPU_H

#include "memory.h"

class CPU
{
    Memory RAM;
    Memory programCounter;

public:
    CPU();

    word fetch();
    void decode(word w);
    void execute();
};

#endif // CPU_H
