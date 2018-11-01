#ifndef REGISTEROFFSETOPERAND_H
#define REGISTEROFFSETOPERAND_H

#include "instructionoperand.h"
#include "memory.h"

class RegisterOffsetOperand : public InstructionOperand
{
    byte rMIndex; // Index of the destination register from 0-15
    word rMValue;
public:
    RegisterOffsetOperand(word _w, Memory *_registers);

    virtual int value();
    virtual QString toString();
};

#endif // REGISTEROFFSETOPERAND_H
