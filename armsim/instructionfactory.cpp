#include "instructionfactory.h"

Instruction *InstructionFactory::getDecodedInstruction(word w, Memory *ram, Memory *registers)
{
    word instructionOpcode = Memory::ExtractBits(w, 25, 27) >> 25;
    if (instructionOpcode == 0b001) {
        return new DataProcessingInstruction(w, registers);
    }
    else if (instructionOpcode == 0b000) {
        word bit4 = Memory::ExtractBits(w, 4, 4) >> 4;
        word bit7 = Memory::ExtractBits(w, 7, 7) >> 7;
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
    }
    else if (instructionOpcode == 0b010 || instructionOpcode == 0b011) {
            return new LoadStoreInstruction(w, ram, registers);
    }
    else if (instructionOpcode == 0b101) {
            return new BranchInstruction(w, registers);
    }

    return nullptr;
}
