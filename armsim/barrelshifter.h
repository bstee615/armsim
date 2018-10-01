/* barrelshifter.h
 * Simulates the Barrel Shifter in an ARM microprocessor.
 * Performs bit shifts and rotations.
*/

#ifndef BARRELSHIFTER_H
#define BARRELSHIFTER_H

#include "memory.h"

class BarrelShifter
{
    static word rotateRight(word w);
public:
    // Rotate w right by numRotations bits.
    static word rotateRight(word w, byte numRotations);
};

#endif // BARRELSHIFTER_H
