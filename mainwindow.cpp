#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    _options(options),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->loaderWidget->setFilePath(_options.getFilename());
    ui->loaderWidget->setAmtMemory(_options.getMemory());
}

MainWindow::~MainWindow()
{
    delete ui;
}
