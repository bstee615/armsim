#include "loadstoreinstruction.h"

LoadStoreInstruction::LoadStoreInstruction(word w, Memory *ram, Memory *registers)
{

}

QString LoadStoreInstruction::toString()
{
    return "LoadStoreInstruction: Not implemented.";
}

void LoadStoreInstruction::execute()
{
    // ram[registers[rDIndex]] := addressingMode.value()
    qDebug() << "ldr/str: noop";
}
