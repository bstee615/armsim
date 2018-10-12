#include "loadstoreinstruction.h"
#include "immediateoperand.h"
#include "immediateshiftedregisteroperand.h"
#include "registeroffsetoperand.h"

LoadStoreInstruction::LoadStoreInstruction(word w, Memory *_ram, Memory *_registers)
{
    ram = _ram;
    registers = _registers;
    P = Memory::ExtractBits(w, 24, 24) != 0;
    U = Memory::ExtractBits(w, 23, 23) != 0;
    B = Memory::ExtractBits(w, 22, 22) != 0;
    W = Memory::ExtractBits(w, 21, 21) != 0;
    L = Memory::ExtractBits(w, 20, 20) != 0;
    rNIndex = Memory::ExtractBits(w, 16, 19) >> 16;
    rNValue = registers->ReadWord(rNIndex*4);
    if (rNIndex == 15) rNValue += 8;
    rDIndex = Memory::ExtractBits(w, 12, 15) >> 12;
    rDValue = registers->ReadWord(rDIndex*4);
    if (rDIndex == 15) rDValue += 8;

    if (Memory::ExtractBits(w, 25, 25) != 0) {
        if (Memory::ExtractBits(w, 4, 11) == 0) {
            addressingMode = new RegisterOffsetOperand(w, registers);
        }
        else {
            addressingMode = new ImmediateShiftedRegisterOperand(w, registers);
        }
    }
    else {
        addressingMode = new ImmediateOperand(w);
    }
}

QString LoadStoreInstruction::addressingModeToString()
{
    QString operand2String = addressingMode->toString();
    if (operand2String.compare(QString("#0")) == 0) return QString("");
    else return QString(", %1%2").arg(U ? QString("") : QString("-"),
                                      addressingMode->toString());
}

QString LoadStoreInstruction::toString()
{
    return QString("%1%2 r%3, [r%4%5]%6").arg(L ? QString("ldr") : QString("str"),
                                           B ? QString("b") : QString(""),
                                           QString::number(rDIndex),
                                           QString::number(rNIndex),
                                           addressingModeToString(),
                                           W ? QString("!") : QString(""));
}

void LoadStoreInstruction::execute()
{
    address addr = rNValue;
    if (U) addr += addressingMode->value();
    else addr -= addressingMode->value();
    if (L) {
        word loadedValue = 0;
        if (B) {
            loadedValue = loadedValue | ram->ReadByte(addr);
        }
        else {
            loadedValue = loadedValue | ram->ReadWord(addr);
        }
        registers->WriteWord(rDIndex*4, loadedValue);
    }
    else {
        if (B) {
            ram->WriteByte(addr, (byte)rDValue);
        }
        else {
            ram->WriteWord(addr, rDValue);
        }
    }

    if (W) {
        registers->WriteWord(rNIndex*4, addr);
    }
}
