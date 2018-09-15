#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QWidget>

namespace Ui {
class StackWidget;
}

class StackWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StackWidget(QWidget *parent = nullptr);
    ~StackWidget();

private:
    Ui::StackWidget *ui;
};

#endif // STACKWIDGET_H
