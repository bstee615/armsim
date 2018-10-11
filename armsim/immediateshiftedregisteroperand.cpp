#include "immediateshiftedregisteroperand.h"

ImmediateShiftedRegisterOperand::ImmediateShiftedRegisterOperand(word w, Memory *registers): ShiftedRegisterOperand(w, registers)
{
    immediateShift = Memory::ExtractBits(w, 7, 11) >> 7;
}

QString ImmediateShiftedRegisterOperand::toString()
{
    return QString("r%1%2").arg(QString::number(rMIndex),
                                 immediateShift == 0 ? "" : QString(", %2 #%3").arg(
                                                               QString(ShiftTypeToString[shiftType]),
                                                               QString::number(immediateShift)));
    }

int ImmediateShiftedRegisterOperand::value()
{
    return shiftTypeToMethod(registers->ReadWord(rMIndex), immediateShift, shiftType);
}
