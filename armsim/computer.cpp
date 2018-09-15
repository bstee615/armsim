#include "computer.h"

Computer::Computer()
{
    cpu = CPU();
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
