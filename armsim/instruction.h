#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include "memorytypes.h"

class Instruction
{
protected:
    byte cond;
public:
    virtual QString toString() = 0;
    virtual void execute() = 0;
};

#endif // INSTRUCTION_H
