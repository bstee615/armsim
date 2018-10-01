#ifndef INSTRUCTIONOPERAND_H
#define INSTRUCTIONOPERAND_H

#include <QString>

class InstructionOperand
{
public:
    virtual int value() = 0;
    virtual QString toString() = 0;
};

#endif // INSTRUCTIONOPERAND_H
