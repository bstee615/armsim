#include "terminalwidget.h"
#include "ui_terminalwidget.h"

TerminalWidget::TerminalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerminalWidget)
{
    ui->setupUi(this);

    connect(ui->leTerminalText, SIGNAL(returnPressed()), this, SLOT(on_btnEnterCommand_clicked()));
}

TerminalWidget::~TerminalWidget()
{
    delete ui;
}

void TerminalWidget::runCommand(QString command)
{
    // TODO: noop for now.
}

void TerminalWidget::printCharacter(char c)
{
    ui->leTerminalText->text().append(QChar(c));
}

void TerminalWidget::on_btnEnterCommand_clicked()
{
    runCommand(ui->leTerminalText->text());
    ui->leTerminalText->clear();
}
