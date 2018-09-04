#ifndef LOADER_H
#define LOADER_H

#include <QString>
#include "ram.h"

void loadELFFile(QString filename, RAM& ram);

#endif // LOADER_H
