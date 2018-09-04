#include "ram.h"

RAM::RAM(address size)
{
    qDebug() << "Loader:" << "Initializing RAM with" << size << "bytes.";
    memory = new byte[size];
}
