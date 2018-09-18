#include "filewriter.h"

FileWriter::FileWriter()
{
}

FileWriter::~FileWriter()
{
    stopTrace();
}

void FileWriter::startTrace(QString filename)
{
    qDebug() << "Trace:" << "Starting trace";

    file = new QFile(filename);
    if (file->open(QIODevice::WriteOnly)) {
        stream = new QTextStream(file);
    }
    else {
        qCritical() << "Error starting trace.";
    }
}

void FileWriter::stopTrace()
{
    qDebug() << "Trace:" << "Stopping trace and writing to" << file->fileName();

    stream->flush();
    file->close();

    delete stream;
    stream = nullptr;
    delete file;
    file = nullptr;
}

QTextStream *FileWriter::writeMessage()
{
    if (!isTracing()) throw StreamNotInitializedException();
    return stream;
}

bool FileWriter::isTracing()
{
    return file != nullptr && stream != nullptr;
}
