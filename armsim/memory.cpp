#include "memory.h"
#include <QtMath>

void Memory::testInBounds(word addr)
{
    if (addr >= size) {
        qDebug() << "Memory: Address" << QString::number(addr, 16).prepend("0x") << "out of bounds.";
        throw OutOfBoundsException();
    }
}

Memory::Memory()
{
    memory = nullptr;
    size = 0;
}

Memory::Memory(address _size)
{
    memory = new byte[_size];
    size = _size;
    clearMemory();
}

// Creates a deep clone of the other RAM object.
Memory::Memory(const Memory& other)
{
    Memory& otherNotConst = const_cast<Memory&>(other);
    size = otherNotConst.getSize();
    memory = new byte[size];
    outputData = other.outputData;
    auto otherMemory = other.memory;
    for (address i  = 0; i < size; i ++) {
        memory[i] = otherMemory[i];
    }
}

// Creates a deep clone of the other RAM object.
Memory &Memory::operator=(const Memory &other)
{
    Memory& otherNotConst = const_cast<Memory&>(other);
    size = otherNotConst.getSize();
    memory = new byte[size];
    byte *otherMemory = otherNotConst.getMemory();
    for (address i  = 0; i < size; i ++) {
        memory[i] = otherMemory[i];
    }

    return *this;
}

Memory::~Memory()
{
    if (memory) {
        delete []memory;
        memory = nullptr;
    }
}

word Memory::ReadWord(address addr)
{
    testInBounds(addr);

    word w = 0;

    if (!isValidWordAddress(addr)) {
        return w;
    }

    for (address i = addr+3; i >= addr; i --) {
        w = w | ((word)memory[i] << 8*(i-addr));
        if (i == 0) break;
    }

    return w;
}

halfword Memory::ReadHalfWord(address addr)
{
    testInBounds(addr);

    halfword w = 0;
    if (!isValidHalfWordAddress(addr)) {
        return w;
    }

    for (address i = addr+1; i >= addr; i --) {
        w = w | (halfword)(memory[i] << 8*(i-addr));
        if (i == 0) break;
    }

    return w;
}

byte  Memory::ReadByte(address addr)
{
    testInBounds(addr);

    return memory[addr];
}

void Memory::WriteWord(address addr, word data)
{
    testInBounds(addr);

    if (!isValidWordAddress(addr)) {
        return;
    }

    memory[addr+3] = (byte)(data >> 24);
    memory[addr+2] = (byte)(data >> 16);
    memory[addr+1] = (byte)(data >> 8);
    memory[addr] = (byte)(data);
}

void Memory::WriteHalfWord(address addr, halfword data)
{
    testInBounds(addr);

    if (!isValidHalfWordAddress(addr)) {
        return;
    }

    memory[addr+1] = (byte)(data >> 8);
    memory[addr] = (byte)data;
}

void Memory::WriteByte(address addr, byte data)
{
    if (addr == 0x100000) {
        outputData = new char(data);
    }
    else {
        outputData = nullptr;
    }

    testInBounds(addr);

    memory[addr] = data;
}

int Memory::Checksum()
{
    int32_t cksum = 0;

    for (address i = 0; i < size; i ++) {
        cksum += memory[i] ^ i;
    }

    return cksum;
}

bool Memory::TestFlag(address addr, unsigned int bit)
{
    if (addr > size) {
        qDebug() << "Memory: Address" << QString::number(addr, 16).prepend("0x") << "out of bounds.";
        throw OutOfBoundsException();
        return false;
    }
    if (bit > (sizeof(word)*8)-1) {
        qDebug() << "Invalid bit access" << bit;
        throw InvalidBitException();
        return false;
    }

    word w = ReadWord(addr);
    word mask = (word)(qPow(2, bit));
    return ((w & mask) != 0);
}

void Memory::SetFlag(address addr, unsigned int bit, bool flag)
{
    if (addr > size) {
        qDebug() << "Memory: Address" << QString::number(addr, 16).prepend("0x") << "out of bounds.";
        throw OutOfBoundsException();
        return;
    }
    if (bit > (sizeof(word)*8)-1) {
        qDebug() << "Invalid bit access" << bit;
        throw InvalidBitException();
        return;
    }

    word w = ReadWord(addr);
    word mask = (word)(1 << bit);

    if (flag) {
        w = w | mask;
    }
    else {
        w = w & (~mask);
    }

    WriteWord(addr, w);
}

word Memory::ExtractBits(word w, unsigned int startBit, unsigned int endBit)
{
    if (startBit > endBit || endBit > 31) {
        throw InvalidBitmaskException();
        return 0;
    }

    word mask = 0;
    for (size_t i = startBit; i <= endBit; i ++) {
        mask = mask | (1 << i);
    }

    return w & mask;
}
