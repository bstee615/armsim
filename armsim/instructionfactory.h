#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include "instruction.h"
#include "loadstoreinstruction.h"
#include "branchinstruction.h"
#include "dataprocessinginstruction.h"

class InstructionFactory {
public:
    static Instruction *getDecodedInstruction(word w, Memory *ram, Memory *registers);
};

#endif // INSTRUCTIONFACTORY_H
