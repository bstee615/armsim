#include "mulinstruction.h"

MultiplyInstruction::MultiplyInstruction(word w, RegisterMemory *_registers):
    Instruction(w, _registers)
{
    S = Memory::ExtractBits(w, 20, 20) != 0;
    rDIndex = Memory::ExtractBits(w, 16, 19) >> 16;
    rSIndex = Memory::ExtractBits(w, 8, 11) >> 8;
    rSValue = registers->getRegisterValue(rSIndex);
    rMIndex = Memory::ExtractBits(w, 0, 3) >> 0;
    rMValue = registers->getRegisterValue(rMIndex);
}

QString MultiplyInstruction::toString()
{
    return QString("mul%1 r%2, r%3, r%4").arg(CC_STR, QString::number(rDIndex), QString::number(rMIndex), QString::number(rSIndex));
}

void MultiplyInstruction::execute()
{
    word rSValue = registers->getRegisterValue(rSIndex);
    if (rSIndex == 15) {
        rSValue += 8;
    }
    word rMValue = registers->getRegisterValue(rMIndex);
    if (rMIndex == 15) {
        rMValue += 8;
    }
    registers->setRegisterValue(rDIndex, rSValue * rMValue);
}
