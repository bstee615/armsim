#include "ram.h"

RAM::RAM()
{
    memory = nullptr;
    size = 0;
}

RAM::RAM(address size)
{
    memory = new byte[size];
    this->size = size;
    for (address i  = 0; i < size; i ++) {
        memory[i] = 0;
    }
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
    if (!isValidWordAddress(addr)) {
        return w;
    }
    if (addr > size) {
        throw OutOfBoundsException();
    }

    for (address i = addr+3; i >= addr; i --) {
        w = w | (static_cast<word>(memory[i]) << 4*(i-addr));
        if (i == 0) break;
    }

    return w;
}

halfword RAM::ReadHalfWord(address addr)
{
    halfword w = 0;
    if (!isValidHalfWordAddress(addr)) {
        return w;
    }
    if (addr > size) {
        throw OutOfBoundsException();
    }

    for (address i = addr+1; i >= addr; i --) {
        w = w | (halfword)((halfword)memory[i] << (halfword)4*(i-addr));
        if (i == 0) break;
    }

    return w;
}

byte  RAM::ReadByte(address addr)
{
    if (addr > size) {
        return 0;
    }

    return memory[addr];
}
