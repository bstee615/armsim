#ifndef TERMINALWIDGET_H
#define TERMINALWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class TerminalWidget;
}

class TerminalWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit TerminalWidget(QWidget *parent = nullptr);
    ~TerminalWidget();

    void runCommand(QString command);

private slots:
    void on_btnEnterCommand_clicked();

private:
    Ui::TerminalWidget *ui;
};

#endif // TERMINALWIDGET_H
