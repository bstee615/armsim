/* loaderwidget.cpp
 * Contains Qt Widget for the Loader phase.
 */

#include "loaderwidget.h"
#include "ui_loaderwidget.h"

// Qt Widget class to encapsulate Loader UI.
LoaderWidget::LoaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoaderWidget)
{
    ui->setupUi(this);
}

LoaderWidget::~LoaderWidget()
{
    delete ui;
}

void LoaderWidget::setFilePath(QString path)
{
    qDebug() << "Loader:" << "File path:" << path;
    ui->filepathLineEdit->setText(path);
}

void LoaderWidget::setAmtMemory(unsigned amt)
{
    qDebug() << "Loader:" << "Amount memory:" << amt;
    ui->memorySpinBox->setValue(static_cast<int>(amt));

    ram = RAM(amt);
}

void LoaderWidget::on_initRAMButton_clicked()
{
    ram = RAM(static_cast<unsigned long>(ui->memorySpinBox->value()));
}

void LoaderWidget::on_loadFileButton_clicked()
{
    qDebug() << "Loader:" << "Loading file:" << ui->filepathLineEdit->text();
    // TODO: Load file.
}
