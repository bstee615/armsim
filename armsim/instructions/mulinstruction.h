#ifndef MULINSTRUCTION_H
#define MULINSTRUCTION_H

#include <QString>
#include "memory.h"
#include "instruction.h"

class MultiplyInstruction: public Instruction
{
    byte rDIndex;
    byte rMIndex;
    word rMValue;
    byte rSIndex;
    word rSValue;
    bool S;

public:
    MultiplyInstruction(word w, Memory *_registers);

    QString toString() override;
    void execute() override;
};

#endif // MULINSTRUCTION_H
