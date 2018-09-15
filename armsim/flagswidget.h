#ifndef FLAGSWIDGET_H
#define FLAGSWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class FlagsWidget;
}

class FlagsWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit FlagsWidget(QWidget *parent = nullptr);
    ~FlagsWidget();

private:
    Ui::FlagsWidget *ui;
};

#endif // FLAGSWIDGET_H
