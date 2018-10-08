/* instruction.h
 * Abstract class modeling a 32-bit instruction.
*/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include "memorytypes.h"

class Instruction
{
protected:
    byte cond; // 4 condition bits

public:
    // Returns an assembly representation of this instruction.
    virtual QString toString() = 0;
    // Executes this instruction on the referenced memory (ram/registers).
    virtual void execute() = 0;
};

#endif // INSTRUCTION_H