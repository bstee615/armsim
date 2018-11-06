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
    ui->terminalWindow->append(QString(c));
}

void TerminalWidget::init(Computer *computer)
{
    ComputerWidget::init(computer);
    ui->terminalWindow->setComputer(_computer);
}
