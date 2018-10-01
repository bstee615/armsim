#include "registershiftedregisteroperand.h"

RegisterShiftedRegisterOperand::RegisterShiftedRegisterOperand(word w): ShiftedRegisterOperand(w, registers)
{

}

QString RegisterShiftedRegisterOperand::toString()
{
    return "RegisterShiftedOperand: Not implemented.";
}

int RegisterShiftedRegisterOperand::value()
{
    return 0;
}
