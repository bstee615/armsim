/* ram.h
 * Contains logic for simulated RAM.
 */

#ifndef RAM_H
#define RAM_H

#include <cstdint>
typedef uint8_t byte;
typedef uint16_t halfword;
typedef uint32_t word;
typedef uint32_t address;

#include <QDebug>
#include <exception>

struct OutOfBoundsException : public std::exception
{
    const char * what () const noexcept
    {
        return "Out of Bounds";
    }
};

struct InvalidBitException : public std::exception
{
    const char * what () const noexcept
    {
        return "Invalid bit";
    }
};

// Class that represents simulated RAM as an array.
class RAM
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

public:
    RAM();
    RAM(address size);
    RAM(const RAM& other);
    RAM& operator=(const RAM& other);
    ~RAM();

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
    void ExtractBits(word word, unsigned int startBit, unsigned int endBit);

    address getSize() { return size; }
    // Method so that tests can get the array representing memory.
    byte *getMemory() { return memory; }

    void clearMemory()
    {
        for (address i  = 0; i < size; i ++) {
            memory[i] = 0;
        }
    }
};

#endif // RAM_H
