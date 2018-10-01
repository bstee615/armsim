#include "barrelshifter.h"

word BarrelShifter::rotateRight(word w)
{
    return (w >> 1) | (w << 31);
}

word BarrelShifter::rotateRight(word w, byte numRotations)
{
    for (int i = 0; i < numRotations; i ++) {
        w = rotateRight(w);
    }

    return w;
}
