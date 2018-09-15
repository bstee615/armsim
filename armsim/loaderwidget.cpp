/* loaderwidget.cpp
 * Contains Qt Widget for the Loader phase.
 */

#include "loaderwidget.h"
#include "ui_loaderwidget.h"
#include "loader.h"
#include <QFileDialog>

// Qt Widget class to encapsulate Loader UI.
LoaderWidget::LoaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoaderWidget)
{
    ui->setupUi(this);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::lightGray);
    palette->setColor(QPalette::Text,Qt::black);
    ui->filepathLineEdit->setPalette(*palette);
}

LoaderWidget::~LoaderWidget()
{
    delete ui;
}

void LoaderWidget::loadFile(QString filepath)
{
    _computer->loadFile(filepath);
    setFileDialogText(filepath);
}

void LoaderWidget::setFileDialogText(QString path)
{
    ui->filepathLineEdit->setText(path);
}

void LoaderWidget::on_loadFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open ELF executable", ".", "ELF Files (*)");
    loadFile(filePath);
}
