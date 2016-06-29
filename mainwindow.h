#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "xmlsaveparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_moneyEdit_editingFinished();

    void on_listWidgetItemID_itemClicked(QListWidgetItem *item);

    void on_checkBoxPrototype_stateChanged(int arg1);

    void on_checkBoxBlueprint_stateChanged(int arg1);

    void on_checkBoxRes_stateChanged(int arg1);

private:
    XMLSaveParser saveEditor;
    Ui::MainWindow *ui;
    void getFromSaveCurrentMoney();
    void getFromSaveItems();
    int currentItemSelected;
};

#endif // MAINWINDOW_H
