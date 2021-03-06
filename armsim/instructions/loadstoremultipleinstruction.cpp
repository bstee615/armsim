#include "loadstoremultipleinstruction.h"
#include <QDebug>

LoadStoreMultipleInstruction::LoadStoreMultipleInstruction(word w, Memory *_ram, RegisterMemory *_registers):
    Instruction(w, _registers)
{
    ram = _ram;
    P = Memory::ExtractBits(w, 24, 24) != 0;
    U = Memory::ExtractBits(w, 23, 23) != 0;
    S = Memory::ExtractBits(w, 22, 22) != 0;
    W = Memory::ExtractBits(w, 21, 21) != 0;
    L = Memory::ExtractBits(w, 20, 20) != 0;

    rNIndex = Memory::ExtractBits(w, 16, 19) >> 16;
    rNValue = registers->getRegisterValue(rNIndex);
    registerList = (halfword)Memory::ExtractBits(w, 0, 15);
}

bool registerIsSetInList(halfword registerList, int i) {
    return ((registerList >> i) & 1) != 0;
}

QString registerListToString(halfword registerList) {
    QString str;
    for (int i = 0; i < 16; i ++) {
        if (registerIsSetInList(registerList, i)) {
            if (!str.isEmpty()) str.append(", ");
            str.append(QString("r%1").arg(i));
        }
    }

    return str;
}

QString operationToString(bool L, bool U, bool P) {
    return QString(L ? "ldm" : "stm").append(U ? "i" : "d").append(P ? "b" : "a");
}

QString LoadStoreMultipleInstruction::toString()
{
    // example: ldmia r13!, {r2, r4, r6}
    return QString("%1%2 r%3%4, { %5 }").arg(
                operationToString(L, U, P),
                CC_STR,
                QString::number(rNIndex),
                W ? QString("!") : QString(""),
                registerListToString(registerList));
}

void LoadStoreMultipleInstruction::execute()
{
    word currentAddress = rNValue;
    for (int in = 0; in < 16; in ++) {
        int i = L ? in : 15-in;
        if (registerIsSetInList(registerList, i)) {
            int changeInBytes = U ? 4 : -4;
            if (P) currentAddress += changeInBytes;

            if (L) registers->setRegisterValue(i, ram->ReadWord(currentAddress));
            else ram->WriteWord(currentAddress, registers->getRegisterValue(i));

            if (!P) currentAddress += changeInBytes;
        }
    }

    if (W) {
        registers->setRegisterValue(rNIndex, currentAddress);
    }
}
