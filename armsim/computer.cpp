#include "computer.h"

Computer::Computer(address numBytes, QString path)
{
    ram = Memory(numBytes);
    cpu = CPU(&ram);
    loadFile(path);
}

void Computer::loadFile(QString path)
{
    if (path.isEmpty()) {
        return;
    }

    if (!loadELF(path, &cpu)) {
        QCoreApplication::exit(1);
        exit(1);
    }
}

void Computer::run()
{
    const word halt = 0;
    while (step() != halt)
    {
        // Do nothing for now.
    }
}

word Computer::step()
{
    word w = cpu.fetch();
    cpu.decode(w);
    cpu.execute();

    return w;
}
