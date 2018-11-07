#include "registershiftedregisteroperand.h"

RegisterShiftedRegisterOperand::RegisterShiftedRegisterOperand(word w, RegisterMemory *_registers): ShiftedRegisterOperand(w, _registers)
{
    rSIndex = Memory::ExtractBits(w, 8, 11) >> 8;
    rSValue = registers->getRegisterValue(rSIndex);
}

QString RegisterShiftedRegisterOperand::toString()
{
    return QString("r%1, %2 r%3").arg(QString::number(rMIndex), QString(ShiftTypeToString[shiftType]), QString::number(rSIndex));
}

int RegisterShiftedRegisterOperand::value()
{
    return shiftTypeToMethod(rMValue, rSValue, shiftType);
}
