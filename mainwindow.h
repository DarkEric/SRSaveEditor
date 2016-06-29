#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QVector>
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

    void updateColor();
private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_moneyEdit_editingFinished();

    void on_checkBoxPrototype_stateChanged(int arg1);

    void on_checkBoxBlueprint_stateChanged(int arg1);

    void on_pushButtonResearchAll_clicked();

    void on_pushButton_clicked();

    void on_listWidgetImplant_itemSelectionChanged();

    void on_listWidgetEquip_itemSelectionChanged();

    void on_listWidgetWeapon_itemSelectionChanged();

    void on_listWidgetDevice_itemSelectionChanged();

    void on_listWidgetUndet_itemSelectionChanged();

private:
    XMLSaveParser saveEditor;
    Ui::MainWindow *ui;
    void getFromSaveCurrentMoney();
    void getFromSaveItems();
    QListWidgetItem* currentItemSelected;
    QString currentTable;
    int currentRow;
    int currentID;
    QColor getColor(int ID);
    QVector<int> weapon;
    QVector<int> devices;
    QVector<int> equips;
    QVector<int> implants;
    QVector<int> other;
};

#endif // MAINWINDOW_H
