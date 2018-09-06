#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include "ram.h"

bool loadELF(QString filename, RAM& ram);

#endif // LOADER_H
