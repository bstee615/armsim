#include "dataprocessinginstruction.h"
#include "rotatedimmediateoperand.h"
#include "registershiftedregisteroperand.h"
#include "immediateshiftedregisteroperand.h"
#include <QDebug>

const char * const DataProcessingInstruction::DataProcessingOpcodeToString [16] = {
    "and", "eor", "sub", "rsb", "add", "adc", "sbc", "rsc", "tst", "teq", "cmp", "cmn", "orr", "mov", "bic", "mvn"
};

InstructionOperand *getAddressingMode(word w, Memory *registers) {
    if (Memory::ExtractBits(w, 25, 25) != 0) {
        return new RotatedImmediateOperand(w);
    }
    else {
        if (Memory::ExtractBits(w, 4, 4) != 0) {
            return new RegisterShiftedRegisterOperand(w, registers);
        }
        else {
            return new ImmediateShiftedRegisterOperand(w, registers);
        }
    }
}

DataProcessingInstruction::DataProcessingInstruction(word w, Memory *_registers)
{
    opcode = (DataProcessingOpcode)(Memory::ExtractBits(w, 21, 24) >> 21);
    s = Memory::ExtractBits(w, 20, 20) != 0;
    rNIndex = (byte)(Memory::ExtractBits(w, 16, 19) >> 16);
    rDIndex = (byte)(Memory::ExtractBits(w, 12, 15) >> 12);
    registers = _registers;
    addressingMode = getAddressingMode(w, registers);
}

DataProcessingInstruction::~DataProcessingInstruction()
{
    delete addressingMode;
}

QString DataProcessingInstruction::toString()
{
    QString opcodeDependentPortion;

    switch (opcode) {
    case MOV:
    case MVN:
        opcodeDependentPortion = QString("r%1, %2").arg(QString::number(rDIndex), addressingMode->toString());
        break;
    case ADD:
    case SUB:
    case RSB:
    case AND:
    case ORR:
    case EOR:
    case BIC:
        opcodeDependentPortion = QString("r%1, r%2, %3").arg(QString::number(rDIndex), QString::number(rNIndex), addressingMode->toString());
        break;
    default:
        opcodeDependentPortion = QString("instruction: not implemented yet.");
        break;
    }

    return QString("%1 %2").arg(QString(DataProcessingOpcodeToString[opcode]), opcodeDependentPortion);
}

void DataProcessingInstruction::execute()
{
    word destinationValue;
    word rNValue = registers->ReadWord(rNIndex*4);

    switch (opcode) {
    case MOV:
        destinationValue = addressingMode->value();
        break;
    case MVN:
        destinationValue = ~addressingMode->value();
        break;
    case ADD:
        destinationValue = rNValue + addressingMode->value();
        break;
    case SUB:
        destinationValue = rNValue - addressingMode->value();
        break;
    case RSB:
        destinationValue = addressingMode->value() - rNValue;
        break;
    case AND:
        destinationValue = rNValue & addressingMode->value();
        break;
    case ORR:
        destinationValue = rNValue | addressingMode->value();
        break;
    case EOR:
        destinationValue = rNValue ^ addressingMode->value();
        break;
    case BIC:
        destinationValue = rNValue & (~addressingMode->value());
        break;
    default:
        destinationValue = 0;
        break;
    }

    registers->WriteWord(rDIndex * 4, destinationValue);
}
