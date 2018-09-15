#ifndef REGISTERSWIDGET_H
#define REGISTERSWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class RegistersWidget;
}

class RegistersWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit RegistersWidget(QWidget *parent = nullptr);
    ~RegistersWidget();

private:
    Ui::RegistersWidget *ui;
};

#endif // REGISTERSWIDGET_H
