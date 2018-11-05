#ifndef BRANCHINSTRUCTION_H
#define BRANCHINSTRUCTION_H

#include "registermemory.h"
#include "instruction.h"

class BranchInstruction : public Instruction
{
    int offset;
    bool L;
    word pcValue;

public:
    BranchInstruction(word w, RegisterMemory *_registers);

    QString toString() override;
    void execute() override;
};

#endif // BRANCHINSTRUCTION_H
