#include "registershiftedregisteroperand.h"

RegisterShiftedRegisterOperand::RegisterShiftedRegisterOperand(word w): ShiftedRegisterOperand(w, registers)
{
    // rSIndex := rSIndex(w)
}

QString RegisterShiftedRegisterOperand::toString()
{
    // example: r6, lsl r7
    return "RegisterShiftedOperand: Not implemented.";
}

int RegisterShiftedRegisterOperand::value()
{
    // return registers[rMIndex] << registers[rSIndex];
    return 0;
}
