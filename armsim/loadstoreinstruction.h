#ifndef LOADSTOREINSTRUCTION_H
#define LOADSTOREINSTRUCTION_H

#include <QString>
#include "memory.h"
#include "instruction.h"
#include "instructionoperand.h"

class LoadStoreInstruction: public Instruction
{
    bool p;
    bool u;
    bool b;
    bool w;
    bool l;

    Memory *ram;
    Memory *registers;
    byte *rDIndex;
    byte *rNIndex;

    InstructionOperand *addressingMode;

public:
    LoadStoreInstruction(word w, Memory *ram, Memory *registers);

    QString toString();
    void execute();
};

#endif // LOADSTOREINSTRUCTION_H
