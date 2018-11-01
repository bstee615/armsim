#ifndef INSTRUCTIONUTILS_H
#define INSTRUCTIONUTILS_H

#include "memory.h"

word getRegisterValue(byte index, Memory *registers)
{
    word value = registers->ReadWord(index*4);
    if (index == 15) {
        value += 8;
    }
    return value;
}

#endif // INSTRUCTIONUTILS_H
