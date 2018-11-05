/* instruction.h
 * Abstract class modeling a 32-bit instruction.
*/

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include "registermemory.h"

#define CC_STR QString(ConditionCodeToString[cond])

class Instruction
{
protected:
    byte cond; // 4 condition bits
    RegisterMemory *registers;

    enum ConditionCode {
        EQ, NE, CS, CC, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, AL, XX // XX for unpredictable
    };

    // An array of strings with one string corresponding to each data processing instruction opcode.
    static const char * const ConditionCodeToString [16];

public:
    Instruction(word w, RegisterMemory *_registers);

    // Returns an assembly representation of this instruction.
    virtual QString toString() = 0;
    // Executes this instruction on the referenced memory (ram/registers).
    virtual void execute() = 0;

    bool shouldExecute();
    bool flagIsSet(NZCFFlag flag);
};

#endif // INSTRUCTION_H
