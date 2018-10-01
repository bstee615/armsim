#include "instructionfactory.h"

Instruction *InstructionFactory::getDecodedInstruction(word w, Memory *ram, Memory *registers)
{
    word instructionOpcode = Memory::ExtractBits(w, 25, 27) >> 25;
    word bit4;
    word bit7;

    switch (instructionOpcode) {
    case 0b000:
        bit4 = Memory::ExtractBits(w, 4, 4) >> 4;
        bit7 = Memory::ExtractBits(w, 7, 7) >> 7;
        if (bit4 == 0) {
            return new DataProcessingInstruction(w, registers);
        }
        else {
            if (bit7 == 0) {
                return new DataProcessingInstruction(w, registers);
            }
            else {
//                return new MultiplyInstruction(w, registers);
            }
        }
    case 0b001:
        return new DataProcessingInstruction(w, registers);
    case 0b010:
    case 0b011:
        return new LoadStoreInstruction(w, ram, registers);
    case 0b100:
        return new LoadStoreMultipleInstruction(w, ram, registers);
    case 0b111:
        if (Memory::ExtractBits(w, 24, 24) >> 24 == 1) {
            return new SoftwareInterruptInstruction(w);
        }
        else {
            // Other instructions with an opcode of 0b111
            break;
        }
    }

    return nullptr;
}
