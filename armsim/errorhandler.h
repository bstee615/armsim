/* errorhandler.h
 * Contains an error handler to hook into the Qt debugging output.
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QCoreApplication>
#include <QtGlobal>
#include <stdio.h>
#include <iostream>

// An error handler to redirect Qt debugging output to the desired location.
void errorHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type) {
        case QtDebugMsg:
            fprintf(stdout, "%s\n", msg.toStdString().c_str());
            fflush(stdout);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical error: %s\n", msg.toStdString().c_str());
            fprintf(stderr, "Press enter to continue.");
            std::cin.ignore();
            QCoreApplication::exit(1);
            exit(1);
    }
}
#endif // ERRORHANDLER_H