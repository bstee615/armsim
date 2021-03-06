#include "dataprocessinginstruction.h"
#include "rotatedimmediateoperand.h"
#include "registershiftedregisteroperand.h"
#include "immediateshiftedregisteroperand.h"
#include <QDebug>

const char * const DataProcessingInstruction::DataProcessingOpcodeToString [16] = {
    "and", "eor", "sub", "rsb", "add", "adc", "sbc", "rsc", "tst", "teq", "cmp", "cmn", "orr", "mov", "bic", "mvn"
};

DataProcessingInstruction::DataProcessingInstruction(word w, RegisterMemory *_registers):
    Instruction(w, _registers)
{
    opcode = (DataProcessingOpcode)(Memory::ExtractBits(w, 21, 24) >> 21);
    S = Memory::ExtractBits(w, 20, 20) != 0;
    rNIndex = (byte)(Memory::ExtractBits(w, 16, 19) >> 16);
    rDIndex = (byte)(Memory::ExtractBits(w, 12, 15) >> 12);
    rNValue = registers->getRegisterValue(rNIndex);
    addressingMode = getAddressingMode(w, registers);
}

InstructionOperand *DataProcessingInstruction::getAddressingMode(word w, RegisterMemory *registers) {
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

void DataProcessingInstruction::cmp(word uval1, word uval2)
{
    word uresult = uval1 - uval2;
    int sval1 = uval1;
    int sval2 = uval2;
    int sresult = uresult;

    registers->SetFlag(CPSR_OFFSET, 31, Memory::ExtractBits(uresult, 31, 31) != 0); // N
    registers->SetFlag(CPSR_OFFSET, 30, uresult == 0); // Z
    registers->SetFlag(CPSR_OFFSET, 29, uval2 <= uval1); // C
    registers->SetFlag(CPSR_OFFSET, 28, (sval1 > 0 && sval2 < 0 && sresult < 0) ||
                       (sval1 < 0 && sval2 > 0 && sresult > 0)); // F
}

void DataProcessingInstruction::cmn(word uval1, word uval2)
{
    word uresult = uval1 - uval2;
    int sval1 = uval1;
    int sval2 = uval2;
    int sresult = uresult;

    registers->SetFlag(CPSR_OFFSET, 31, Memory::ExtractBits(uresult, 31, 31) != 0); // N
    registers->SetFlag(CPSR_OFFSET, 30, uresult == 0); // Z
    registers->SetFlag(CPSR_OFFSET, 29, false); // C
    registers->SetFlag(CPSR_OFFSET, 28, (sval1 > 0 && sval2 < 0 && sresult < 0) ||
                       (sval1 < 0 && sval2 > 0 && sresult > 0)); // F
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
        opcodeDependentPortion = QString("r%1, r%2").arg(QString::number(rDIndex), addressingMode->toString());
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
    case CMP:
    case CMN:
        opcodeDependentPortion = QString("r%1, %2").arg(QString::number(rNIndex), addressingMode->toString());
        break;
    default:
        opcodeDependentPortion = QString("instruction: not implemented yet.");
        break;
    }

    QString SFlag = (S && opcode != CMP && opcode != CMN) ? QString("s") : QString("");
    return QString("%1%2%3 %4").arg(QString(DataProcessingOpcodeToString[opcode]), SFlag, CC_STR, opcodeDependentPortion);
}

void DataProcessingInstruction::execute()
{
    word destinationValue = 0;

    switch (opcode) {
    case MOV:
        destinationValue = addressingMode->value();
        if (S && rDIndex == 15) {
            registers->setCPSR(registers->getSPSR());
        }
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
    case CMP:
        cmp(rNValue, addressingMode->value());
        break;
    case CMN:
        cmn(rNValue, -addressingMode->value());
        break;
    default:
        break;
    }

    if (opcode != CMP && opcode != CMN) {
        registers->setRegisterValue(rDIndex, destinationValue);
    }
}
