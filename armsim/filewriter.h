#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QFile>
#include <QTextStream>
#include <QDebug>

struct StreamNotInitializedException : public std::exception
{
    const char * what () const noexcept
    {
        return "Stream not initialized";
    }
};

class FileWriter
{
    QFile *file = nullptr;
    QTextStream *stream = nullptr;

public:
    FileWriter();
    ~FileWriter();

    void startTrace(QString filename);
    void stopTrace();

    QTextStream *writeMessage();

    bool isTracing();
};

#endif // FILEWRITER_H
