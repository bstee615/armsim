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

bool RegisterShiftedRegisterOperand::CarryFlag()
{
    word firstEightBits = Memory::ExtractBits(rSValue, 0, 7);
    switch (shiftType) {
    case lsl:
        if (firstEightBits == 0) {
            return registers->getNZCF(Carry);
        }
        else if (firstEightBits < 32) {
            return Memory::ExtractBits(rMValue, 32 - firstEightBits, 32 - firstEightBits) != 0;
        }
        else if (firstEightBits == 32) {
            return Memory::ExtractBits(rMValue, 0, 0) != 0;
        }
        else {
            return false;
        }
        break;
    case lsr:
        if (firstEightBits == 0) {
            return registers->getNZCF(Carry);
        }
        else if (firstEightBits < 32) {
            return Memory::ExtractBits(rMValue, firstEightBits - 1, firstEightBits - 1) != 0;
        }
        else if (firstEightBits == 32) {
            return Memory::ExtractBits(rMValue, 31, 31) != 0;
        }
        else {
            return false;
        }
        break;
    case asr:
        if (firstEightBits == 0) {
            return registers->getNZCF(Carry);
        }
        else if (firstEightBits < 32) {
            return Memory::ExtractBits(rMValue, firstEightBits - 1, firstEightBits - 1) != 0;
        }
        else {
            Memory::ExtractBits(rMValue, 31, 31) != 0;
            return false;
        }
        break;
    case ror:
        if (firstEightBits == 0) {
            return registers->getNZCF(Carry);
        }
        else if (Memory::ExtractBits(rSValue, 0, 4) == 0) {
            return Memory::ExtractBits(rMValue, 31, 31) != 0;
        }
        else {
            return Memory::ExtractBits(rMValue, Memory::ExtractBits(rSValue, 0, 4) - 1, Memory::ExtractBits(rSValue, 0, 4) - 1) != 0;
        }
        break;
    }
}
