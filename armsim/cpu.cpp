#include "cpu.h"
#include <chrono>
#include <thread>

CPU::CPU(Memory &ram): _ram(ram), registers(Memory()) // TODO: Calculate the correct number of bytes.
{
}

word CPU::fetch()
{
    auto addressToFetch = registers.ReadWord(PC_OFFSET);
    return _ram.ReadWord(addressToFetch);
}

void CPU::decode(word w)
{

}

void CPU::execute()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
}
