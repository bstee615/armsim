#include "runcontrolswidget.h"
#include "ui_runcontrolswidget.h"
#include <QShortcut>

RunControlsWidget::RunControlsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RunControlsWidget)
{
    ui->setupUi(this);

    btnRun = ui->btnRun;
    btnStep = ui->btnStep;
    btnStop = ui->btnStop;

    popup = new AddBreakpointPopup(this);
    connect(popup, SIGNAL(addedBreakpoint()), this, SLOT(onAddedBreakpoint()));
}

RunControlsWidget::~RunControlsWidget()
{
    delete popup;
    delete ui;
}

void RunControlsWidget::init(Computer *computer)
{
    ComputerWidget::init(computer);
    popup->init(_computer);

    new QShortcut(QKeySequence(Qt::Key_F5), ui->btnRun, SLOT(click()));
    new QShortcut(QKeySequence(Qt::Key_F10), ui->btnStep, SLOT(click()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), ui->btnStop, SLOT(click()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_T), this, SLOT(toggleTrace()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_B), this, SLOT(on_btnAddBreakpoint_clicked()));
}

void RunControlsWidget::startTrace()
{
    ui->checkTrace->setChecked(true);
}

void RunControlsWidget::setRunningState(bool running)
{
    ui->btnRun->setEnabled(!running);
    ui->btnStep->setEnabled(!running);
    ui->btnStop->setEnabled(running);
}

void RunControlsWidget::on_btnRun_clicked()
{
    setRunningState(true);
}

void RunControlsWidget::on_btnStep_clicked()
{
    setRunningState(true);
}

void RunControlsWidget::on_btnStop_clicked()
{
    setRunningState(false);
}

void RunControlsWidget::on_btnAddBreakpoint_clicked()
{
    popup->show();
}

void RunControlsWidget::onAddedBreakpoint()
{
    emit toggledBreakpoint();
}

void RunControlsWidget::on_checkTrace_stateChanged(int state)
{
    if (state == Qt::Checked) {
        _computer->startTrace("trace.log");
    } else {
        _computer->stopTrace();
    }
}

void RunControlsWidget::toggleTrace()
{
    ui->checkTrace->toggle();
}
