#include "loadstoreinstruction.h"
#include "immediateoperand.h"

LoadStoreInstruction::LoadStoreInstruction(word w, Memory *_ram, Memory *_registers)
{
    P = Memory::ExtractBits(w, 24, 24) != 0;
    U = Memory::ExtractBits(w, 23, 23) != 0;
    B = Memory::ExtractBits(w, 22, 22) != 0;
    W = Memory::ExtractBits(w, 21, 21) != 0;
    L = Memory::ExtractBits(w, 20, 20) != 0;
    rNIndex = Memory::ExtractBits(w, 16, 19) >> 16;
    rDIndex = Memory::ExtractBits(w, 12, 15) >> 12;
    ram = _ram;
    registers = _registers;
    addressingMode = new ImmediateOperand(w);
}

QString LoadStoreInstruction::toString()
{
    return QString("%1%2 r%3, [%4]%5").arg(L ? QString("ldr") : QString("ldr"),
                                           B ? QString("b") : QString(""),
                                           QString::number(rDIndex),
                                           addressingMode->toString(),
                                           W ? QString("!") : QString(""));
}

void LoadStoreInstruction::execute()
{
    word rDValue = registers->ReadWord(rDIndex*4);
    if (rDIndex == 15) {
        rDValue += 8;
    }
    if (L) {
        word loadedValue;
        if (B) {
            loadedValue = ram->ReadByte(addressingMode->value());
        }
        else {
            loadedValue = ram->ReadWord(addressingMode->value());
        }
        registers->WriteWord(rDIndex*4, loadedValue);
    }
    else {
        if (B) {
            ram->WriteByte(addressingMode->value(), (byte)rDValue);
        }
        else {
            ram->WriteWord(addressingMode->value(), rDValue);
        }
    }
}
