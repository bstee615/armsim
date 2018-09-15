#ifndef RUNCONTROLSWIDGET_H
#define RUNCONTROLSWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class RunControlsWidget;
}

class RunControlsWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit RunControlsWidget(QWidget *parent = nullptr);
    ~RunControlsWidget();

private slots:
    void on_btnRun_clicked();

    void on_btnStep_clicked();

private:
    Ui::RunControlsWidget *ui;
};

#endif // RUNCONTROLSWIDGET_H
