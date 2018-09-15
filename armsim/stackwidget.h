#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class StackWidget;
}

class StackWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit StackWidget(QWidget *parent = nullptr);
    ~StackWidget();

private:
    Ui::StackWidget *ui;
};

#endif // STACKWIDGET_H
