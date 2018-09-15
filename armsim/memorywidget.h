#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include "computerwidget.h"

namespace Ui {
class MemoryWidget;
}

class MemoryWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

public:
    explicit MemoryWidget(QWidget *parent = nullptr);
    ~MemoryWidget();

private:
    Ui::MemoryWidget *ui;
};

#endif // MEMORYWIDGET_H
