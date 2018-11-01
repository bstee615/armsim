#include "instructionoperand.h"

word InstructionOperand::getRegisterValue(byte index)
{
    word value = registers->ReadWord(index*4);
    if (index == 15) {
        value += 8;
    }
    return value;
}
