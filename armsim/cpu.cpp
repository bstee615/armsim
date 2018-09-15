#include "cpu.h"
#include <chrono>
#include <thread>

CPU::CPU()
{

}

word CPU::fetch()
{
    auto addressToFetch = programCounter.ReadWord(0);
    return ram.ReadWord(addressToFetch);
}

void CPU::decode(word w)
{

}

void CPU::execute()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
}
