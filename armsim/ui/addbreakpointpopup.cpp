#include "addbreakpointpopup.h"
#include "ui_addbreakpointpopup.h"

AddBreakpointPopup::AddBreakpointPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBreakpointPopup)
{
    ui->setupUi(this);
    lastValue = ui->spinBox->value();
}

AddBreakpointPopup::~AddBreakpointPopup()
{
    delete ui;
}

void AddBreakpointPopup::on_buttonBox_accepted()
{
    lastValue = ui->spinBox->hexValue();
    _computer->toggleBreakpoint((address)lastValue);
    this->hide();

    emit addedBreakpoint();
}

void AddBreakpointPopup::on_buttonBox_rejected()
{
    ui->spinBox->setHexValue(lastValue);
    this->hide();
}
