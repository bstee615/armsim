#ifndef BARRELSHIFTER_H
#define BARRELSHIFTER_H

#include "memory.h"

class BarrelShifter
{
public:
    static word rotateRight(word w);
    static word rotateRight(word w, byte numRotations);
};

#endif // BARRELSHIFTER_H
