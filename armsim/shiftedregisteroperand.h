#ifndef SHIFTEDREGISTEROPERAND_H
#define SHIFTEDREGISTEROPERAND_H

#include "instructionoperand.h"
#include "memory.h"

enum ShiftType {
    lsl = 0,
    asl = 1,
    lsr = 2,
    rorrrx = 3
};

class ShiftedRegisterOperand: public InstructionOperand
{
protected:
    Memory *registers;
    byte rDIndex;
    ShiftType shiftType;

public:
    ShiftedRegisterOperand(word w, Memory *registers);

    virtual int value() = 0;
    virtual QString toString() = 0;
};

#endif // SHIFTEDREGISTEROPERAND_H
