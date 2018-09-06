#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QtGlobal>
#include <stdio.h>

void errorHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch (type) {
        case QtDebugMsg:
            fprintf(stdout, "%s\n", msg.toStdString().c_str());
            fflush(stdout);
            break;
        case QtWarningMsg:
            fprintf(stderr, "\033[31mWarning\033[0m %s line %d: %s\n", context.file, context.line, msg.toStdString().c_str());
            break;
        case QtCriticalMsg:
            fprintf(stderr, "\033[31mCritical\033[0m %s line %d: %s\n", context.file, context.line, msg.toStdString().c_str());
            break;
        case QtFatalMsg:
            fprintf(stderr, "\033[31mFatal\033[0m %s line %d: %s\n", context.file, context.line, msg.toStdString().c_str());
            abort();
    }
}
#endif // ERRORHANDLER_H
