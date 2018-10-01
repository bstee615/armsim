#ifndef BRANCHINSTRUCTION_H
#define BRANCHINSTRUCTION_H

#include <QString>
#include "instruction.h"
#include "memory.h"

class BranchInstruction: public Instruction
{
    Memory *registers;
    bool link;
    address offset;

public:
    BranchInstruction(word w, Memory *registers);

    QString toString();
    void execute();
};

#endif // BRANCHINSTRUCTION_H
