/* loaderwidget.h
 * Contains a custom Qt widget for displaying loader info.
 */

#ifndef LOADERWIDGET_H
#define LOADERWIDGET_H

#include "memory.h"
#include <QWidget>
#include <QDebug>

// Qt magic "header" for the Widgets app.
namespace Ui {
class LoaderWidget;
}

class LoaderWidget : public QWidget
{
    Q_OBJECT

    Ui::LoaderWidget *ui;
    Memory ram;

public:
    explicit LoaderWidget(QWidget *parent = nullptr);
    ~LoaderWidget();

    Memory &getRAM()
    {
        return ram;
    }

    // Loads the specified file and updates the GUI.
    void loadFile(QString path);

    // Sets the ram field to a new instance of a RAM object with the specified number of bytes.
    void initializeRAM(unsigned amt);

private slots:
    // Event handler for the init. RAM button.
    void on_initRAMButton_clicked();

    // Event handler for the Load File button.
    void on_loadFileButton_clicked();
};

#endif // LOADERWIDGET_H
