#include "immediateshiftedregisteroperand.h"

ImmediateShiftedRegisterOperand::ImmediateShiftedRegisterOperand(word w, Memory *registers): ShiftedRegisterOperand(w, registers)
{

}

QString ImmediateShiftedRegisterOperand::toString()
{
    // example: r4, lsl 8
    return "ImmediateShiftedRegister: Not implemented.";
}

int ImmediateShiftedRegisterOperand::value()
{
    // return registers[rMIndex] << immediateShift;
    return 0;
}
