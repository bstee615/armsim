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
    bool _test;
public:
    Options(QString filename, numbytes memory, bool test): _filename(filename), _memory(memory), _test(test) { }

    QString getFilename() { return _filename; }
    numbytes getMemory() { return _memory; }
    bool isTestFlagSet() { return _test; }
};

#endif // OPTIONS_H
