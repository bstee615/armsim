#ifndef LOADERWIDGET_H
#define LOADERWIDGET_H

#include "ram.h"
#include <QWidget>
#include <QDebug>

namespace Ui {
class LoaderWidget;
}

class LoaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoaderWidget(QWidget *parent = nullptr);
    ~LoaderWidget();

    RAM &getRAM()
    {
        return ram;
    }
    void loadFile(QString path);
    void initializeRAM(unsigned amt);

private slots:
    void on_initRAMButton_clicked();

    void on_loadFileButton_clicked();

private:
    Ui::LoaderWidget *ui;
    RAM ram;
};

#endif // LOADERWIDGET_H
