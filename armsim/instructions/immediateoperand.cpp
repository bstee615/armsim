#include "immediateoperand.h"
#include "memory.h"

ImmediateOperand::ImmediateOperand(word w)
{
    immediate = Memory::ExtractBits(w, 0, 11);
}

QString ImmediateOperand::toString()
{
    // example: #15
    return QString("#%1").arg(immediate, 0, 10);
}

int ImmediateOperand::value()
{
    return immediate;
}
