#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"
#include "loader.h"
#include "ocomputer.h"
#include <QCoreApplication>

class Computer: public OComputer
{
    CPU cpu;
    Memory ram;

public:
    Computer(address numBytes, QString path);
    void loadFile(QString path);

    // Calls the CPU's fetch(), decode(), and execute() in a loop, until fetch() returns a 0.
    void run(bool *shouldStop);
    // Call the CPU's fetch(), decode(), and execute() methods once.
    word step();
};

#endif // COMPUTER_H
