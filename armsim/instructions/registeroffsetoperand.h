#ifndef REGISTEROFFSETOPERAND_H
#define REGISTEROFFSETOPERAND_H

#include "instructionoperand.h"
#include "registermemory.h"

class RegisterOffsetOperand : public InstructionOperand
{
    byte rMIndex; // Index of the destination register from 0-15
    word rMValue;
public:
    RegisterOffsetOperand(word _w, RegisterMemory *_registers);

    virtual int value() override;
    virtual QString toString() override;
};

#endif // REGISTEROFFSETOPERAND_H
