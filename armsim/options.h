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
public:
    QString filename;
    numbytes memory;
    bool execFlag;
    bool traceAll;

    Options() { }
};

#endif // OPTIONS_H
