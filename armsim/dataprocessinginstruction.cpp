#include "dataprocessinginstruction.h"
#include "rotatedimmediateoperand.h"
#include <QDebug>

const char * const DataProcessingInstruction::DataProcessingOpcodeToString [] = {
    "and", "eor", "sub", "rsb", "add", "adc", "sbc", "rsc", "tst", "teq", "cmp", "cmn", "orr", "mov", "bic", "mvn"
};

DataProcessingInstruction::DataProcessingInstruction(word w, Memory *registers)
{
    opcode = (DataProcessingOpcode)(Memory::ExtractBits(w, 21, 24) >> 21);
    s = Memory::ExtractBits(w, 20, 20) != 0;
    rNIndex = (byte)(Memory::ExtractBits(w, 16, 19) >> 16);
    rDIndex = (byte)(Memory::ExtractBits(w, 12, 15) >> 12);
    this->registers = registers;
    addressingMode = new RotatedImmediateOperand(w);
}

QString DataProcessingInstruction::toString()
{
    switch (opcode) {
    case MOV:
        return QString("%1 r%2, %4").arg(QString(DataProcessingOpcodeToString[opcode]), QString::number(rDIndex), addressingMode->toString());
    default:
        return QString("%1 instruction type not implemented.").arg(QString(DataProcessingOpcodeToString[opcode]));
    }
}

void DataProcessingInstruction::execute()
{
    switch (opcode) {
    case MOV:
        registers->WriteWord(rDIndex * 4, addressingMode->value());
        break;
    default:
        qDebug() << toString();
        break;
    }
}
