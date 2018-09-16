#ifndef COMPUTER_H
#define COMPUTER_H

#include "cpu.h"
#include "loader.h"
#include "ocomputer.h"
#include <QCoreApplication>
#include <QThread>

class Computer: public OComputer
{
    CPU cpu;
    Memory ram;

public:
    Computer(address numBytes, QString path);
    void loadFile(QString path);

    // Calls the CPU's fetch(), decode(), and execute() in a loop, until fetch() returns a 0.
    void run();
    // Call the CPU's fetch(), decode(), and execute() methods once.
    word step();
};

class ComputerRunThread : public QThread
{
    Q_OBJECT
    void run() { _computer->run(); }

    Computer *_computer;

public:
    ComputerRunThread(Computer *computer) { _computer = computer; }
};

class ComputerStepThread : public QThread
{
    Q_OBJECT
    void run() { _computer->step(); }

    Computer *_computer;

public:
    ComputerStepThread(Computer *computer) { _computer = computer; }
};

#endif // COMPUTER_H
