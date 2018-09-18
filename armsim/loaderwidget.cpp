/* loaderwidget.cpp
 * Contains Qt Widget for the Loader phase.
 */

#include "loaderwidget.h"
#include "ui_loaderwidget.h"
#include "loader.h"
#include <QFileDialog>
#include <QShortcut>

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

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(on_loadFileButton_clicked()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this, SLOT(on_initRAMButton_clicked()));
}

LoaderWidget::~LoaderWidget()
{
    delete ui;
}

void LoaderWidget::loadFile(QString filepath)
{
    _computer->loadFile(filepath);
    setFileDialogText(filepath);
    ui->lblChecksum->setText(QString("%1").arg(_computer->cpu.getChecksum(), 8, 10, QChar('0')));

    emit loadedFile();
}

void LoaderWidget::setFileDialogText(QString path)
{
    ui->filepathLineEdit->setText(path);
}

void LoaderWidget::on_loadFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open ELF executable", ".", "ELF Files (*)");
    if (filePath.isEmpty()) return;
    loadFile(filePath);
}

void LoaderWidget::on_initRAMButton_clicked()
{
    loadFile(ui->filepathLineEdit->text());
}
