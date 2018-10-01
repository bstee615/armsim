/* instructionoperand
 * Abstract class modeling an addressing mode operand.
*/

#ifndef INSTRUCTIONOPERAND_H
#define INSTRUCTIONOPERAND_H

#include <QString>

class InstructionOperand
{
public:
    // Returns the calculated value of this operand.
    virtual int value() = 0;
    virtual QString toString() = 0;
};

#endif // INSTRUCTIONOPERAND_H
