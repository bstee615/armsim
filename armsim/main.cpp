/* main.cpp
 * Contains the entry method into the program and command line parsing.
**/

#include "mainwindow.h"
#include "options.h"
#include "errorhandler.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QtGlobal>

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

    parser.process(app);
    if (parser.positionalArguments().length() > 0) {
        QStringList invalidOptionsFormatted = QStringList();
        for (int i = 0; i < parser.positionalArguments().length(); i ++) {
            invalidOptionsFormatted.insert(i, "'" + parser.positionalArguments().at(i) + "'");
        }
        qCritical(QString("Unknown options " + invalidOptionsFormatted.join(", ")).toStdString().c_str());
        app.exit();
        exit(1);
    }

    QString loadValue = parser.value(loadOption);
    unsigned memValue = parser.value(memOption).toUInt();

    return Options(loadValue, memValue);
}

// Entry method into the program.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("armsim");
    QApplication::setApplicationVersion("1.0");

//    qInstallMessageHandler(errorHandler);

    Options options = parseCommandLine(app);

    MainWindow window(options);
    window.show();

    return app.exec();
}
