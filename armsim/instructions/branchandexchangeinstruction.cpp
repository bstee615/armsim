#include "branchandexchangeinstruction.h"

BranchAndExchangeInstruction::BranchAndExchangeInstruction(word w, Memory *_registers)
{
    registers = _registers;
    byte rMIndex = Memory::ExtractBits(w, 0, 3);
    rMValue = getRegisterValue(rMIndex);
}

QString BranchAndExchangeInstruction::toString()
{
    return QString("bx #%1").arg(QString::number(rMValue));
}

void BranchAndExchangeInstruction::execute()
{
    registers->WriteWord(15 * 4, rMValue);
}
