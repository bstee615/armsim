#include "registeroffsetoperand.h"

RegisterOffsetOperand::RegisterOffsetOperand(word _w, Memory *_registers)
{
    registers = _registers;
    rMIndex = Memory::ExtractBits(_w, 0, 3);
    rMValue = registers->ReadWord(rMIndex*4);
    if (rMIndex == 15) rMValue += 8;
}

int RegisterOffsetOperand::value()
{
    return rMValue;
}

QString RegisterOffsetOperand::toString()
{
    return QString("r%1").arg(QString::number(rMIndex));
}
