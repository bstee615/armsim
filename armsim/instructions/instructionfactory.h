/* instruction factory.h
 * static class containing a factory method for Instructions.
*/

#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include "registermemory.h"
#include "instruction.h"

class InstructionFactory {
public:
    // Looks at the bits in w and instantiates the appropriate instruction type,
    //  with references to the Memory instances in the CPU.
    static Instruction *getDecodedInstruction(word w, Memory *ram, RegisterMemory *registers);
};

#endif // INSTRUCTIONFACTORY_H
