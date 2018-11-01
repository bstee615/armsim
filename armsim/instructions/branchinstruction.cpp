#include "branchinstruction.h"

BranchInstruction::BranchInstruction(word w, Memory *_registers)
{
    offset = Memory::ExtractBits(w, 0, 23);
    L = Memory::ExtractBits(w, 24, 24) != 0;
    registers = _registers;
}

QString BranchInstruction::toString()
{
    return QString("b%1 #%2", L ? "l" : "", offset);
}

void BranchInstruction::execute()
{
    word pcValue = registers->ReadWord(15 * 4);
    registers->WriteWord(15 * 4, pcValue + offset);
}
