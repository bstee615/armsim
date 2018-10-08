#include "barrelshifter.h"

word BarrelShifter::ror(word w)
{
    return (w >> 1) | (w << 31);
}

word BarrelShifter::ror(word w, byte numRotations)
{
    for (int i = 0; i < numRotations; i ++) {
        w = ror(w);
    }

    return w;
}

word BarrelShifter::lsl(word w, byte numShifts)
{
    return w << numShifts;
}

word BarrelShifter::lsr(word w, byte numShifts)
{
    return w >> numShifts;
}

word BarrelShifter::asr(word w, byte numShifts)
{
    const word sign = w & 0x80000000;
    for (int i = 0; i < numShifts; i ++) {
        w = w >> 1 | sign;
    }

    return w;
}
