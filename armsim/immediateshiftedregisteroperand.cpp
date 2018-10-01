#include "immediateshiftedregisteroperand.h"

ImmediateShiftedRegisterOperand::ImmediateShiftedRegisterOperand(word w, Memory *registers): ShiftedRegisterOperand(w, registers)
{

}

QString ImmediateShiftedRegisterOperand::toString()
{
    return "ImmediateShiftedRegister: Not implemented.";
}

int ImmediateShiftedRegisterOperand::value()
{
    return 0;
}
