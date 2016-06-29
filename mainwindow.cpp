#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QString"
#include "QDebug"
#include "QSettings"
#include "QStandardPaths"
#include "QRegExp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->moneyEdit->setValidator(new QRegExpValidator( QRegExp("\\d{1,7}[.]\\d{1,4}")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getFromSaveCurrentMoney()
{
    ui->moneyEdit->setText(QString::number(saveEditor.getCurrentMoney()));
}

void MainWindow::getFromSaveItems()
{
    QList<int> list = saveEditor.getItemsID();
    for(auto& i:list){
        ui->listWidgetItemID->addItem(QString::number(i));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).at(0);
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open save"),path+"/SatelliteReign/users/",tr("Save Files (*.xml)"));
    if(!saveEditor.openXML(fileName)) qDebug()<<"Error openXML";
    getFromSaveCurrentMoney();
    getFromSaveItems();
}

void MainWindow::on_actionSave_triggered()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).at(0);
    QString fileName = QFileDialog::getSaveFileName(this,tr("Open save"),path+"/SatelliteReign/users/",tr("Save Files (*.xml)"));
    saveEditor.saveXML(fileName);
}

void MainWindow::on_moneyEdit_editingFinished()
{
    saveEditor.setCurrentMoney(ui->moneyEdit->text().toDouble());
}

void MainWindow::on_listWidgetItemID_itemClicked(QListWidgetItem *item)
{
    currentItemSelected = item->text().toInt();
    ui->checkBoxPrototype->setChecked(saveEditor.getItemHasPrototype(currentItemSelected));
    ui->checkBoxBlueprint->setChecked(saveEditor.getItemHasBlueprints(currentItemSelected));
    ui->checkBoxRes->setChecked(saveEditor.getItemResearchStarted(currentItemSelected));
}

void MainWindow::on_checkBoxPrototype_stateChanged(int arg1)
{
    saveEditor.setItemHasPrototype(currentItemSelected,arg1);
}

void MainWindow::on_checkBoxBlueprint_stateChanged(int arg1)
{
    saveEditor.setItemHasBlueprints(currentItemSelected,arg1);
}

void MainWindow::on_checkBoxRes_stateChanged(int arg1)
{
    saveEditor.setItemResearchStarted(currentItemSelected,arg1);
}
