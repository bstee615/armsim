/* barrelshifter.h
 * Simulates the Barrel Shifter in an ARM microprocessor.
 * Performs bit shifts and rotations.
*/

#ifndef BARRELSHIFTER_H
#define BARRELSHIFTER_H

#include "memory.h"

class BarrelShifter
{
    // Rotate w right by 1 bit.
    static word ror(word w);
    // Arithmetically shift w right by 1 bit.
    static word asr(word w);
public:
    // Rotate w right by numRotations bits.
    static word ror(word w, word numRotations);

    // Shift w left (don't wrap around) by numRotations bits.
    static word lsl(word w, word numShifts);

    // Shift w right (don't wrap around) by numRotations bits and pad the left with 0's.
    static word lsr(word w, word numShifts);

    // Shift w right (don't wrap around) by numRotations bits and sign-extend the left.
    static word asr(word w, word numShifts);
};

#endif // BARRELSHIFTER_H
