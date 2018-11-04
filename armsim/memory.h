/* ram.h
 * Contains logic for simulated RAM.
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <QDebug>
#include <exception>

#include "memorytypes.h"

// To be thrown when the memory array would have been indexed out of bounds.
struct OutOfBoundsException : public std::exception
{
    const char * what () const noexcept
    {
        return "Out of Bounds";
    }
};

// To be thrown when a function recieves a bit index that's out of the correct range (e.g. [0..31] for a word).
struct InvalidBitException : public std::exception
{
    const char * what () const noexcept
    {
        return "Invalid bit index";
    }
};

// To be thrown when a function recieves bitmask parameters that are invalid (startBit is greater than endBit, startBit is negative, etc.)
struct InvalidBitmaskException : public std::exception
{
    const char * what () const noexcept
    {
        return "Invalid bitmask";
    }
};

// Define register offsets
#define R0_OFFSET 0
#define IP_OFFSET 48
#define SP_OFFSET 52
#define LR_OFFSET 56
#define PC_OFFSET 60
#define CPSR_OFFSET 64

#define NUM_REGISTER_BYTES 68

// Class that represents simulated RAM as an array.
class Memory
{
    byte* memory;
    address size;

    // Helper methods to ensure that addresses are aligned when reading/writing.
    bool isValidWordAddress(address addr)
    {
        return addr % 4 == 0;
    }
    bool isValidHalfWordAddress(address addr)
    {
        return addr % 2 == 0;
    }

    void testInBounds(word addr);

public:
    char *outputData = nullptr;
    Memory();
    Memory(address size);
    Memory(const Memory& other);
    Memory& operator=(const Memory& other);
    ~Memory();

    // Reads a data value of the appropriate size (word/halfword/byte) at the 32-bit address.
    word ReadWord(address addr);
    halfword ReadHalfWord(address addr);
    byte ReadByte(address addr);

    // Receives a 32-bit address and a data value of the appropriate size (word/halfword/byte) and writes it to simulated RAM.
    void WriteWord(address addr, word data);
    void WriteHalfWord(address addr, halfword data);
    void WriteByte(address addr, byte data);

    // Public method to compute the checksum for the contents of simulated RAM.
    int Checksum();

    // Reads the byte at address addr and returns true if bit is 1 in the word or false if 0 (bit is in the range [0..31]).
    bool TestFlag(address addr, unsigned int bit);

    // Reads the word at location addr and sets the bit whose position is specified by bit to 1 if flag is true, or 0 if flag is false.
    void SetFlag(address addr, unsigned int bit, bool flag);

    // Returns the bits in the range [startBit, endBit] from word, where startBit and endBit are in the range [0..31].
    static word ExtractBits(word word, unsigned int startBit, unsigned int endBit);

    address getSize() { return size; }
    // Method so that tests can get the array representing memory.
    byte *getMemory() { return memory; }

    // Sets all bytes in RAM to 0.
    void clearMemory()
    {
        for (address i  = 0; i < size; i ++) {
            memory[i] = 0;
        }
    }

    word *getPointerToMemory(address addr)
    {
        return (word*)(memory + addr);
    }
};

#endif // MEMORY_H
