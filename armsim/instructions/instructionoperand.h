/* instructionoperand
 * Abstract class modeling an addressing mode operand.
*/

#ifndef INSTRUCTIONOPERAND_H
#define INSTRUCTIONOPERAND_H

#include <QString>
#include "memory.h"

class InstructionOperand
{
protected:
    Memory *registers;

public:
    virtual ~InstructionOperand() { }
    // Returns the calculated value of this operand.
    virtual int value() = 0;
    // Returns an assembly representation of the addressing mode, formatted to be used in Instruction::toString().
    virtual QString toString() = 0;

    word getRegisterValue(byte index);
};

#endif // INSTRUCTIONOPERAND_H
