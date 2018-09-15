/* loaderwidget.h
 * Contains a custom Qt widget for displaying loader info.
 */

#ifndef LOADERWIDGET_H
#define LOADERWIDGET_H

#include "memory.h"
#include "computerwidget.h"
#include <QWidget>
#include <QDebug>

// Qt magic "header" for the Widgets app.
namespace Ui {
class LoaderWidget;
}

class LoaderWidget : public QWidget, public ComputerWidget
{
    Q_OBJECT

    Ui::LoaderWidget *ui;

public:
    explicit LoaderWidget(QWidget *parent = nullptr);
    ~LoaderWidget();

    // Loads the specified file and updates the GUI.
    void loadFile(QString path);
    void setFileDialogText(QString path);

private slots:
    // Event handler for the Load File button.
    void on_loadFileButton_clicked();
};

#endif // LOADERWIDGET_H
