#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    ui(new Ui::MainWindow),
    _options(options),
    computer(Computer(_options.getMemory(), _options.getFilename()))
{
    ui->setupUi(this);
    ui->loaderWidget->init(&computer);
    ui->loaderWidget->setFileDialogText(_options.getFilename());

    ui->runControlsWidget->init(&computer);
    connect(ui->runControlsWidget, SIGNAL(updatedUI()), this, SLOT(onUpdatedUI()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onUpdatedUI()
{
    // TODO: Update other sub-widgets that are needed and thank past Benji for this gracious gift.
}
