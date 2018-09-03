#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Options &options, QWidget *parent):
    QMainWindow (parent),
    _options(options),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->filenameValue->setText("\"" + _options.getFilename() + "\"");
    ui->memoryKbValue->setText(QString::number(_options.getMemory()));
    ui->testsValue->setText(_options.isTest() ? "true" : "false");
}

MainWindow::~MainWindow()
{
    delete ui;
}
