/* options.cpp
 * Contains the Options class.
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>
#include <QDebug>


typedef unsigned long int numbytes;

// Options class to encapsulate command line arguments.
class Options
{
    QString _filename;
    numbytes _memory;

public:
    Options(QString filename, numbytes memory): _filename(filename), _memory(memory) { }

    QString getFilename() { return _filename; }
    numbytes getMemory() { return _memory; }
};

#endif // OPTIONS_H
