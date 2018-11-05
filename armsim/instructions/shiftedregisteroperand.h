/* shiftedregisteroperand.h
 * Abstract class to coalesce shared properties of ImmediateShiftedRegisterOperand and RegisterShiftedRegisterOperand.
*/

#ifndef SHIFTEDREGISTEROPERAND_H
#define SHIFTEDREGISTEROPERAND_H

#include "instructionoperand.h"
#include "registermemory.h"

class ShiftedRegisterOperand: public InstructionOperand
{
protected:
    // Enumeration of all shift types, encoded in instructions as a 2-bit integer.
    enum ShiftType {
        lsl = 0,
        lsr = 1,
        asr = 2,
        ror = 3
    };

    static const char * const ShiftTypeToString [4];

    byte rMIndex; // Index of the destination register from 0-15
    word rMValue;
    ShiftType shiftType;

public:
    // Assigns class members for w and registers.
    ShiftedRegisterOperand(word w, RegisterMemory *registers);
    word shiftTypeToMethod(word w, word numShifts, ShiftType shiftType);

    virtual int value() = 0;
    virtual QString toString() = 0;
    byte registerIndex() override;
    virtual bool CarryFlag() override = 0;
};

#endif // SHIFTEDREGISTEROPERAND_H
