#include "terminalwidget.h"
#include "ui_terminalwidget.h"

TerminalWidget::TerminalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerminalWidget)
{
    ui->setupUi(this);
}

TerminalWidget::~TerminalWidget()
{
    delete ui;
}

void TerminalWidget::printCharacter(char c)
{
    ui->terminalWindow->setText(ui->terminalWindow->toPlainText().append(QString(c)));
}

void TerminalWidget::init(Computer *computer)
{
    ComputerWidget::init(computer);
    ui->terminalWindow->setComputer(_computer);
}

void TerminalWidget::updateText()
{
    if (_computer->outputDevice->outputData != nullptr) {
        printCharacter(*_computer->outputDevice->outputData);
    }
    else {
        qCritical() << "Terminal:" << "Output device signal received with no data.";
    }
}
