#include "loadstoremultipleinstruction.h"

LoadStoreMultipleInstruction::LoadStoreMultipleInstruction(word w, Memory *ram, Memory *registers)
{

}

QString LoadStoreMultipleInstruction::toString()
{
    // example: ldmia r13!, {r2, r4, r6}
    return "LoadStoreMultipleInstruction: Not implemented.";
}

void LoadStoreMultipleInstruction::execute()
{
    // int rD := registers[rDIndex]
    // for (0 <= i < 16) {
    //     if ((registerList >> i) & 1 == 1) {
    //         ram[registers[rD]] := registers[i]
    //     }
    //     rD := rD + 4
    // }
    qDebug() << "ldm/stm: noop";
}
