#include "rotatedimmediateoperand.h"
#include "barrelshifter.h"

RotatedImmediateOperand::RotatedImmediateOperand(word encodedWord)
{
    immediate = Memory::ExtractBits(encodedWord, 0, 7);
    rotate = Memory::ExtractBits(encodedWord, 8, 11);
}

int RotatedImmediateOperand::value()
{
    return BarrelShifter::rotateRight(immediate, rotate*2);
}

QString RotatedImmediateOperand::toString()
{
    return QString("#%1").arg(value());
}
