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
    word rMValue = registers->ReadWord(rMIndex*4);
    if (rMIndex == 15) {
        rMValue += 8;
    }
    word rSValue = registers->ReadWord(rSIndex*4);
    if (rSIndex == 15) {
        rSValue += 8;
    }
    return shiftTypeToMethod(rMValue, rSValue, shiftType);
}
