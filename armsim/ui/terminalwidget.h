#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <QWidget>
#include "computerwidget.h"
#include <QTextBrowser>
#include <QKeyEvent>

namespace Ui {
class TerminalWidget;
}

class TerminalTextBrowser: public QTextBrowser {
    Q_OBJECT
    Computer *_computer;

public:
    TerminalTextBrowser(QWidget *parent = nullptr): QTextBrowser(parent) {

    }

    void keyPressEvent(QKeyEvent *ev) {
        // Source: https://forum.qt.io/topic/10198/get-string-value-from-modified-key-press/2
        int key = ev->key();
        if(key >= Qt::Key_Space && key <= Qt::Key_AsciiTilde) {
            // handle ASCII char like keys
            _computer->handleInputCharacter(QChar(key).toLatin1());
        }
    }

    void setComputer(Computer *computer) {
        _computer = computer;
    }
};

class TerminalWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void printCharacter(char c);

private:
    Ui::TerminalWidget *ui;
};

#endif // TERMINALWIDGET_H
