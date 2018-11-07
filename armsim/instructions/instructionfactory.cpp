#include "instructionfactory.h"
#include "softwareinterruptinstruction.h"
#include "loadstoremultipleinstruction.h"
#include "loadstoreinstruction.h"
#include "dataprocessinginstruction.h"
#include "branchinstruction.h"
#include "branchandexchangeinstruction.h"
#include "mulinstruction.h"
#include "statusregisterinstruction.h"

Instruction *InstructionFactory::getDecodedInstruction(word w, Memory *ram, RegisterMemory *registers)
{
    word _23thru27 = Memory::ExtractBits(w, 23, 27) >> 23;
    word _20thru21 = Memory::ExtractBits(w, 20, 21) >> 20;
    word _4thru7 = Memory::ExtractBits(w, 4, 7) >> 4;
    if ((((_23thru27 == 0b00110 || _23thru27 == 0b00010) && _20thru21 == 0b10) && _4thru7 == 0) ||
         (_23thru27 == 0b00010 && _20thru21 == 0b00)) {
        return new StatusRegisterInstruction(w, registers);
    }

    word instructionOpcode = Memory::ExtractBits(w, 25, 27) >> 25;
    word bit4;
    word bit7;
    byte nybble1;
    byte nybble5;

    switch (instructionOpcode) {
    case 0b000:
        bit4 = Memory::ExtractBits(w, 4, 4) >> 4;
        bit7 = Memory::ExtractBits(w, 7, 7) >> 7;

        nybble5 = Memory::ExtractBits(w, 20, 23) >> 20;
        nybble1 = Memory::ExtractBits(w, 4, 7) >> 4;
        if (nybble5 == 2 && nybble1 == 1) {
            return new BranchAndExchangeInstruction(w, registers);
        }
        else {
            if (bit4 == 0) {
                return new DataProcessingInstruction(w, registers);
            }
            else {
                if (bit7 == 0) {
                    return new DataProcessingInstruction(w, registers);
                }
                else {
                    return new MultiplyInstruction(w, registers);
                }
            }
        }
        break;
    case 0b001:
        return new DataProcessingInstruction(w, registers);
    case 0b010:
    case 0b011:
        return new LoadStoreInstruction(w, ram, registers);
    case 0b100:
        return new LoadStoreMultipleInstruction(w, ram, registers);
    case 0b101:
        return new BranchInstruction(w, registers);
        break;
    case 0b111:
        if (Memory::ExtractBits(w, 24, 24) >> 24 == 1) {
            return new SoftwareInterruptInstruction(w, registers);
        }
        else {
            // Other instructions with an opcode of 0b111
            break;
        }
    default:
        break;
    }
    qDebug() << QString("Unrecognized instruction %1").arg(QString::number(w, 16).prepend("0x"));

    return nullptr;
}
