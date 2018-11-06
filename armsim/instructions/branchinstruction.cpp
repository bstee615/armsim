#include "branchinstruction.h"

BranchInstruction::BranchInstruction(word w, RegisterMemory *_registers):
    Instruction(w, _registers)
{
    word imm = (Memory::ExtractBits(w, 0, 23));
    if ((imm & 0x800000) != 0) {
        imm = imm | 0xFF000000;
    }
    offset = imm << 2;
    L = Memory::ExtractBits(w, 24, 24) != 0;
    pcValue = registers->getRegisterValue(15);
}

QString BranchInstruction::toString()
{
    return QString("b%1%2 #%3").arg(L ? QString("l") : QString(""), CC_STR, QString::number((int)pcValue + offset));
}

void BranchInstruction::execute()
{
    registers->setRegisterValue(15, pcValue + offset);
    if (L) {
        registers->setRegisterValue(14, pcValue - 4);
    }
}
