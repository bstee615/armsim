#include "immediateshiftedregisteroperand.h"

ImmediateShiftedRegisterOperand::ImmediateShiftedRegisterOperand(word w, RegisterMemory *registers): ShiftedRegisterOperand(w, registers)
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
    return shiftTypeToMethod(rMValue, immediateShift, shiftType);
}

bool ImmediateShiftedRegisterOperand::CarryFlag()
{
    switch (shiftType) {
    case lsl:
        if (immediateShift == 0) {
            return registers->getNZCF(Carry);
        }
        else {
            return Memory::ExtractBits(rMValue, 32 - immediateShift, 32 - immediateShift) != 0;
        }
        break;
    case lsr:
        if (immediateShift == 0) {
            return Memory::ExtractBits(rMValue, 31, 31) != 0;
        }
        else  {
            return Memory::ExtractBits(rMValue, immediateShift - 1, immediateShift - 1) != 0;
        }
        break;
    case asr:
        if (immediateShift == 0) {
            return Memory::ExtractBits(rMValue, 31, 31) != 0;
        }
        else {
            return Memory::ExtractBits(rMValue, immediateShift - 1, immediateShift - 1) != 0;
        }
        break;
    case ror:
        if (immediateShift == 0) {
            return Memory::ExtractBits(rMValue, 0, 0) != 0;
        }
        else {
            return Memory::ExtractBits(rMValue, immediateShift - 1, immediateShift - 1) != 0;
        }
        break;
    }
}
