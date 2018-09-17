#include "computer.h"

Computer::Computer(address numBytes)
{
    ram = Memory(numBytes);
    cpu = CPU(&ram);
}

void Computer::loadFile(QString path)
{
    if (path.isEmpty()) {
        return;
    }

    if (!loadELF(path, &cpu)) {
        qCritical() << "Error:" << "Exiting application.";
        QCoreApplication::exit(1);
        exit(1);
    }
}

void Computer::run(bool *shouldStop)
{
    const word halt = 0;
    while (!(*shouldStop) && step() != halt && !breakpoints.contains(cpu.getProgramCounter()))
    {
        // Do nothing for now.
    }
}

word Computer::step()
{
    word w = cpu.fetch();
    cpu.decode(w);
    cpu.execute();
    qDebug() << "Computer:" << "Executed word" << QString("%1").arg(w, 8, 16, QChar('0')).toUpper().prepend(QString("0x"));

    return w;
}

bool Computer::isBreakpoint(address addr)
{
    return breakpoints.contains(addr);
}

void Computer::addBreakpoint(address addr)
{
    breakpoints.insert(addr);
}
