#ifndef BRANCHINSTRUCTION_H
#define BRANCHINSTRUCTION_H

#include "memory.h"
#include "instruction.h"

class BranchInstruction : public Instruction
{
    int offset;
    bool L;
    word pcValue;

public:
    BranchInstruction(word w, Memory *_registers);

    QString toString() override;
    void execute() override;
};

#endif // BRANCHINSTRUCTION_H
