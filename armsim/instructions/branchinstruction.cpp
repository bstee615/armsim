#include "branchinstruction.h"

BranchInstruction::BranchInstruction(word w, Memory *_registers)
{
    registers = _registers;
    offset = Memory::ExtractBits(w, 0, 23) << 2;
    L = Memory::ExtractBits(w, 24, 24) != 0;
    pcValue = getRegisterValue(15);
}

QString BranchInstruction::toString()
{
    return QString("b%1 #%2").arg(L ? QString("l") : QString(""), QString::number(offset));
}

void BranchInstruction::execute()
{
    registers->WriteWord(15 * 4, pcValue + offset);
    if (L) {
        registers->WriteWord(14 * 4, pcValue - 4);
    }
}
