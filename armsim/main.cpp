/* main.cpp
 * Contains the entry method into the program and command line parsing.
**/

#include "ui/mainwindow.h"
#include "options.h"
#include "errorhandler.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QtGlobal>

#define EXIT_APP { QCoreApplication::exit(1);exit(1); }

const QString LOAD_OPTION_NAME = "load";
const QString MEM_OPTION_NAME = "mem";

Options getValidatedOptions(QCommandLineParser &parser)
{
    if (parser.positionalArguments().length() > 0) {
        QStringList invalidOptionsFormatted = QStringList();
        for (int i = 0; i < parser.positionalArguments().length(); i ++) {
            invalidOptionsFormatted.insert(i, "'" + parser.positionalArguments().at(i) + "'");
        }
        qCritical(QString("Unknown options " + invalidOptionsFormatted.join(", ")).toStdString().c_str());
        EXIT_APP;
    }

    QString loadValue = parser.value(LOAD_OPTION_NAME);
    unsigned memValue = parser.value(MEM_OPTION_NAME).toUInt();
    if (memValue == 0 || memValue > 1000000) {
        qCritical() << "Loader:" << "Invalid --mem argument:" << parser.value(MEM_OPTION_NAME);
        EXIT_APP;
    }

    return Options(loadValue, memValue);
}

// Helper method to use a Qt command line parser.
Options parseCommandLine(QCoreApplication &app)
{
    QCommandLineParser parser;
    parser.setApplicationDescription("ArmSim Phase 1: Loader");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption loadOption(QStringList() << LOAD_OPTION_NAME,
            QString("The name of a file in ELF format."),
            QString("filename"));
    parser.addOption(loadOption);

    QCommandLineOption memOption(QStringList() << MEM_OPTION_NAME,
            QString("A number specifying the number of bytes in the simulated RAM. If not specified, the default is 32768."),
            QString("memory"),
            QString("32768"));
    parser.addOption(memOption);

    parser.process(app);
    return getValidatedOptions(parser);
}

// Entry method into the program.
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("armsim");
    QApplication::setApplicationVersion("1.0");

    qInstallMessageHandler(errorHandler);

    Options options = parseCommandLine(app);

    try {
        MainWindow window(options);
        window.show();

        return app.exec();
    }
    catch (std::exception ex) {
        qCritical() << ex.what();
    }
}
