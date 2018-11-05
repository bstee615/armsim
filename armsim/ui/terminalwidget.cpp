#include "terminalwidget.h"
#include "ui_terminalwidget.h"

TerminalWidget::TerminalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerminalWidget)
{
    ui->setupUi(this);
    ui->terminalWindow->setComputer(_computer);
}

TerminalWidget::~TerminalWidget()
{
    delete ui;
}

void TerminalWidget::printCharacter(char c)
{
    ui->terminalWindow->append(QString(c));
}
