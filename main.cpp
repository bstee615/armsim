/* main.cpp
 * Contains the entry method into the program and command line parsing.
**/

#include "mainwindow.h"
#include "options.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

// Helper method to use a Qt command line parser.
Options parseCommandLine(QApplication& app)
{
    QCommandLineParser parser;
    parser.setApplicationDescription("ArmSim Phase 1: Loader");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption loadOption(QStringList() << "load",
            QString("The name of a file in ELF format."),
            QString("filename"));
    parser.addOption(loadOption);

    QCommandLineOption memOption(QStringList() << "mem",
            QString("A number specifying the number of bytes in the simulated RAM. If not specified, the default is 32768."),
            QString("memory"),
            QString("32768"));
    parser.addOption(memOption);

    QCommandLineOption testOption(QStringList() << "test",
            QString("Run tests and quit."));
    parser.addOption(testOption);

    parser.process(app);

    QString loadValue = parser.value(loadOption);
    unsigned memValue = parser.value(memOption).toUInt();
    bool testValue = parser.isSet(testOption);

    return Options(loadValue, memValue, testValue);
}

// Helper method for diagnostic options logging.
void logOptions(Options &options)
{
    qDebug() << "Loader:" << "filename:" << options.getFilename();
    qDebug() << "Loader:" << "bytes of memory:" << options.getMemory();
    qDebug() << "Loader:" << "unit tests:" << options.isTest();
}

// Entry method into the program.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("armsim");
    QApplication::setApplicationVersion("1.0");

    Options options = parseCommandLine(app);
    logOptions(options);

    MainWindow window(options);
    window.show();

    return app.exec();
}
