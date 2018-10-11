#include "mulinstruction.h"

MultiplyInstruction::MultiplyInstruction(word w, Memory *_registers)
{
    registers = _registers;
    S = Memory::ExtractBits(w, 20, 20) != 0;
    rDIndex = Memory::ExtractBits(w, 16, 19) >> 16;
    rSIndex = Memory::ExtractBits(w, 8, 11) >> 8;
    rMIndex = Memory::ExtractBits(w, 0, 3) >> 0;
}

QString MultiplyInstruction::toString()
{
    return QString();
}

void MultiplyInstruction::execute()
{
    word rDValue = registers->ReadWord(rDIndex*4);
    if (rDIndex == 15) {
        rDValue += 8;
    }
    word rSValue = registers->ReadWord(rSIndex*4);
    if (rSIndex == 15) {
        rSValue += 8;
    }
    word rMValue = registers->ReadWord(rMIndex*4);
    if (rMIndex == 15) {
        rMValue += 8;
    }
    registers->WriteWord(rDIndex*4, rSValue * rMValue);
}
