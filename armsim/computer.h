#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"

class Computer
{
    CPU cpu;
public:
    Computer();

    // Calls the CPU's fetch(), decode(), and execute() in a loop, until fetch() returns a 0.
    void run();
    // Call the CPU's fetch(), decode(), and execute() methods once.
    word step();
};

#endif // COMPUTER_H
