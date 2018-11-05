#include "branchandexchangeinstruction.h"

BranchAndExchangeInstruction::BranchAndExchangeInstruction(word w, RegisterMemory *_registers):
    Instruction(w, _registers)
{
    byte rMIndex = Memory::ExtractBits(w, 0, 3);
    rMValue = registers->getRegisterValue(rMIndex);
}

QString BranchAndExchangeInstruction::toString()
{
    return QString("bx%1 #%2").arg(CC_STR, QString::number(rMValue));
}

void BranchAndExchangeInstruction::execute()
{
    registers->setRegisterValue(15, rMValue);
}
