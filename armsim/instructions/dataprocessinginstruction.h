/* dataprocessing.h
 * Models a data processing instruction - AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, BIC, or MVN.
*/

#ifndef DATAPROCESSINGINSTRUCTION_H
#define DATAPROCESSINGINSTRUCTION_H

#include "instruction.h"
#include "instructionoperand.h"
#include "memory.h"

class DataProcessingInstruction : public Instruction
{
    // An enumeration of all data processing instruction opcodes.
    enum DataProcessingOpcode {
        AND, EOR, SUB, RSB, ADD, ADC, SBC, RSC, TST, TEQ, CMP, CMN, ORR, MOV, BIC, MVN
    };

    // An array of strings with one string corresponding to each data processing instruction opcode.
    static const char * const DataProcessingOpcodeToString [16];

    DataProcessingOpcode opcode;
    bool S; // Do / Do not set condition flags
    byte rDIndex; // Index of rD from 0-15
    byte rNIndex; // Index of rN from 0-15
    word rNValue;
    InstructionOperand *addressingMode;

    void cmp(word uval1, word uval2);
    void cmn(word uval1, word uval2);
    void movs();

public:
    DataProcessingInstruction(word w, Memory *registers);
    ~DataProcessingInstruction();

    QString toString() override;
    void execute() override;
};

#endif // DATAPROCESSINGINSTRUCTION_H
