#include "barrelshifter.h"

word BarrelShifter::ror(word w)
{
    return (w >> 1) | (w << 31);
}

word BarrelShifter::ror(word w, word numRotations)
{
    for (size_t i = 0; i < numRotations; i ++) {
        w = ror(w);
    }

    return w;
}

word BarrelShifter::lsl(word w, word numShifts)
{
    return w << numShifts;
}

word BarrelShifter::lsr(word w, word numShifts)
{
    return w >> numShifts;
}

word BarrelShifter::asr(word w, word numShifts)
{
    const word sign = w & 0x80000000;
    for (size_t i = 0; i < numShifts; i ++) {
        w = w >> 1 | sign;
    }

    return w;
}
