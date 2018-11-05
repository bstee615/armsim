#ifndef BRANCHANDEXCHANGEINSTRUCTION_H
#define BRANCHANDEXCHANGEINSTRUCTION_H

#include "memory.h"
#include "instruction.h"

class BranchAndExchangeInstruction: public Instruction
{
    word rMValue;

public:
    BranchAndExchangeInstruction(word w, RegisterMemory *_registers);

    QString toString() override;
    void execute() override;
};

#endif // BRANCHANDEXCHANGEINSTRUCTION_H
