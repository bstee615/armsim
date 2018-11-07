#include "registeroffsetoperand.h"

RegisterOffsetOperand::RegisterOffsetOperand(word _w, RegisterMemory *_registers)
{
    registers = _registers;
    rMIndex = Memory::ExtractBits(_w, 0, 3);
    rMValue = registers->getRegisterValue(rMIndex);
}

int RegisterOffsetOperand::value()
{
    return rMValue;
}

QString RegisterOffsetOperand::toString()
{
    return QString("r%1").arg(QString::number(rMIndex));
}
