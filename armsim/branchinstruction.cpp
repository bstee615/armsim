#include "branchinstruction.h"

BranchInstruction::BranchInstruction(word w, Memory *registers)
{

}

QString BranchInstruction::toString()
{
    return "BranchInstruction: Not implemented.";
}

void BranchInstruction::execute()
{
    qDebug() << "b/bl: noop";
}
