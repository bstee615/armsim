#include "ram.h"
#include <QtMath>

RAM::RAM()
{
    memory = nullptr;
    size = 0;
}

RAM::RAM(address size)
{
    memory = new byte[size];
    this->size = size;
    clearMemory();
}

// Creates a deep clone of the other RAM object.
RAM::RAM(const RAM& other)
{
    RAM& otherNotConst = const_cast<RAM&>(other);
    size = otherNotConst.getSize();
    memory = new byte[size];
    byte *otherMemory = otherNotConst.getMemory();
    for (address i  = 0; i < size; i ++) {
        memory[i] = otherMemory[i];
    }
}

// Creates a deep clone of the other RAM object.
RAM &RAM::operator=(const RAM &other)
{
    RAM& otherNotConst = const_cast<RAM&>(other);
    size = otherNotConst.getSize();
    memory = new byte[size];
    byte *otherMemory = otherNotConst.getMemory();
    for (address i  = 0; i < size; i ++) {
        memory[i] = otherMemory[i];
    }

    return *this;
}

RAM::~RAM()
{
    if (memory) {
        delete []memory;
        memory = nullptr;
    }
}

word RAM::ReadWord(address addr)
{
    word w = 0;
    if (addr >= size) {
        throw OutOfBoundsException();
        return w;
    }
    if (!isValidWordAddress(addr)) {
        return w;
    }

    for (address i = addr+3; i >= addr; i --) {
        w = w | ((word)memory[i] << 8*(i-addr));
        if (i == 0) break;
    }

    return w;
}

halfword RAM::ReadHalfWord(address addr)
{
    halfword w = 0;
    if (addr >= size) {
        throw OutOfBoundsException();
        return w;
    }
    if (!isValidHalfWordAddress(addr)) {
        return w;
    }

    for (address i = addr+1; i >= addr; i --) {
        w = w | (halfword)(memory[i] << 8*(i-addr));
        if (i == 0) break;
    }

    return w;
}

byte  RAM::ReadByte(address addr)
{
    if (addr >= size) {
        throw OutOfBoundsException();
        return 0;
    }

    return memory[addr];
}

void RAM::WriteWord(address addr, word data)
{
    if (addr >= size) {
        throw OutOfBoundsException();
        return;
    }
    if (!isValidWordAddress(addr)) {
        return;
    }

    memory[addr+3] = (byte)(data >> 24);
    memory[addr+2] = (byte)(data >> 16);
    memory[addr+1] = (byte)(data >> 8);
    memory[addr] = (byte)(data);
}

void RAM::WriteHalfWord(address addr, halfword data)
{
    if (addr >= size) {
        throw OutOfBoundsException();
        return;
    }
    if (!isValidHalfWordAddress(addr)) {
        return;
    }

    memory[addr+1] = (byte)(data >> 8);
    memory[addr] = (byte)data;
}

void RAM::WriteByte(address addr, byte data)
{
    if (addr >= size) {
        throw OutOfBoundsException();
        return;
    }

    memory[addr] = data;
}

int RAM::Checksum()
{
    int32_t cksum = 0;

    for (address i = 0; i < size; i ++) {
        cksum += memory[i] ^ i;
    }

    return cksum;
}

bool RAM::TestFlag(address addr, unsigned int bit)
{
    word w = ReadWord(addr);
    word mask = (word)(qPow(2, bit));
    return ((w & mask) != 0);
}

void RAM::SetFlag(address addr, unsigned int bit, bool flag)
{
    word w = ReadWord(addr);
    word mask = flag ? (word)(qPow(2, bit)) : 0;

    if (flag) {
        w = w | mask;
    }
    else {
        w = w & (~mask);
    }

    WriteWord(addr, w);
}
