#include "registershiftedregisteroperand.h"

RegisterShiftedRegisterOperand::RegisterShiftedRegisterOperand(word w, Memory *_registers): ShiftedRegisterOperand(w, _registers)
{
     rSIndex = Memory::ExtractBits(w, 8, 11) >> 8;
}

QString RegisterShiftedRegisterOperand::toString()
{
    return QString("r%1, %2 r%3").arg(QString::number(rMIndex), QString(ShiftTypeToString[shiftType]), QString::number(rSIndex));
}

int RegisterShiftedRegisterOperand::value()
{
    return shiftTypeToMethod(registers->ReadWord(rMIndex), registers->ReadWord(rSIndex), shiftType);
}
