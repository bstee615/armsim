/* shiftedregisteroperand.h
 * Abstract class to coalesce shared properties of ImmediateShiftedRegisterOperand and RegisterShiftedRegisterOperand.
*/

#ifndef SHIFTEDREGISTEROPERAND_H
#define SHIFTEDREGISTEROPERAND_H

#include "instructionoperand.h"
#include "memory.h"

class ShiftedRegisterOperand: public InstructionOperand
{
protected:
    // Enumeration of all shift types, encoded in instructions as a 2-bit integer.
    enum ShiftType {
        lsl = 0,
        asl = 1,
        lsr = 2,
        rorrrx = 3
    };

    Memory *registers; // A reference to the register memory instance from the CPU.
    byte rMIndex; // Index of the destination register from 0-15
    ShiftType shiftType;

public:
    // Assigns class members for w and registers.
    ShiftedRegisterOperand(word w, Memory *registers);

    virtual int value() = 0;
    virtual QString toString() = 0;
};

#endif // SHIFTEDREGISTEROPERAND_H
