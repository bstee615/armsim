#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"
#include "loader.h"
#include <QCoreApplication>
#include <QSet>

class Computer
{
public:
    CPU cpu;
    Memory ram;
    QSet<address> breakpoints;

    Computer(address numBytes, QString path);
    void loadFile(QString path);

    // Calls the CPU's fetch(), decode(), and execute() in a loop, until fetch() returns a 0.
    void run(bool *shouldStop);
    // Call the CPU's fetch(), decode(), and execute() methods once.
    word step();

    bool isBreakpoint(address addr);
    void addBreakpoint(address addr);
};

#endif // COMPUTER_H
