#ifndef DATAPROCESSINGINSTRUCTION_H
#define DATAPROCESSINGINSTRUCTION_H

#include "memory.h"
#include "instruction.h"
#include "instructionoperand.h"

class DataProcessingInstruction : public Instruction
{
    enum DataProcessingOpcode {
        AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, BIC, MVN
    };

    static const char * const DataProcessingOpcodeToString [];

    DataProcessingOpcode opcode;
    bool s;
    Memory *registers;
    byte rDIndex;
    byte rNIndex;
    InstructionOperand *addressingMode;

public:
    DataProcessingInstruction(word w, Memory *registers);

    QString toString();
    void execute();
};

#endif // DATAPROCESSINGINSTRUCTION_H
