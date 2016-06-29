#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QString"
#include "QDebug"
#include "QSettings"
#include "QStandardPaths"
#include "QRegExp"
#include "sets.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->moneyEdit->setValidator(new QRegExpValidator( QRegExp("\\d{1,7}[.]\\d{0,4}")));
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
    Sets* sets = Sets::getInstance();
    QList<int> list = saveEditor.getItemsID();
    weapon.resize(list.size());
    devices.resize(list.size());
    equips.resize(list.size());
    implants.resize(list.size());
    other.resize(list.size());
    for(auto& i:list){
        if(sets->devices.contains(i)){
            devices[ui->listWidgetDevice->count()]=i;
            ui->listWidgetDevice->addItem(sets->devices[i]);
        }else if (sets->weapons.contains(i)){
            weapon[ui->listWidgetWeapon->count()]=i;
            ui->listWidgetWeapon->addItem(sets->weapons[i]);
        }else if (sets->equips.contains(i)){
            equips[ui->listWidgetEquip->count()]=i;
            ui->listWidgetEquip->addItem(sets->equips[i]);
        }else if (sets->implants.contains(i)){
            implants[ui->listWidgetImplant->count()]=i;
            ui->listWidgetImplant->addItem(sets->implants[i]);
        }else{
            other[ui->listWidgetUndet->count()]=i;
            if(sets->other.contains(i)){
                ui->listWidgetUndet->addItem(sets->other[i]);
            }else
                ui->listWidgetUndet->addItem(QString::number(i));
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).at(0);
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open save"),path+"/SatelliteReign/users/",tr("Save Files (*.xml)"));
    if(!saveEditor.openXML(fileName)) qDebug()<<"Error openXML";
    currentItemSelected = NULL;
    ui->listWidgetDevice->clear();
    ui->listWidgetEquip->clear();
    ui->listWidgetImplant->clear();
    ui->listWidgetUndet->clear();
    ui->listWidgetWeapon->clear();
    getFromSaveCurrentMoney();
    getFromSaveItems();
    updateColor();
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

void MainWindow::on_checkBoxPrototype_stateChanged(int arg1)
{
    saveEditor.setItemHasPrototype(currentID,arg1);
    currentItemSelected->setBackgroundColor(getColor(currentID));
}

void MainWindow::on_checkBoxBlueprint_stateChanged(int arg1)
{
    saveEditor.setItemHasBlueprints(currentID,arg1);
    currentItemSelected->setBackgroundColor(getColor(currentID));
}

void MainWindow::updateColor()
{
    int n = ui->listWidgetDevice->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* item = ui->listWidgetDevice->item(i);
        int Row = ui->listWidgetDevice->row(item);
        int ID = devices[Row];
        item->setBackgroundColor(getColor(ID));
    }
    n = ui->listWidgetEquip->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* item = ui->listWidgetEquip->item(i);
        int Row = ui->listWidgetEquip->row(item);
        int ID = equips[Row];
        item->setBackgroundColor(getColor(ID));
    }
    n = ui->listWidgetImplant->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* item = ui->listWidgetImplant->item(i);
        int Row = ui->listWidgetImplant->row(item);
        int ID = implants[Row];
        item->setBackgroundColor(getColor(ID));
    }
    n = ui->listWidgetUndet->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* item = ui->listWidgetUndet->item(i);
        int Row = ui->listWidgetUndet->row(item);
        int ID = other[Row];
        item->setBackgroundColor(getColor(ID));
    }
    n = ui->listWidgetWeapon->count();
    for(int i=0;i<n;i++)
    {
        QListWidgetItem* item = ui->listWidgetWeapon->item(i);
        int Row = ui->listWidgetWeapon->row(item);
        int ID = weapon[Row];
        item->setBackgroundColor(getColor(ID));
    }
}

QColor MainWindow::getColor(int ID)
{
    int prot = 100 * saveEditor.getItemHasPrototype(ID) + 100;
    int blue = 100;
    int res = 100 * saveEditor.getItemHasBlueprints(ID) + 100;
    return QColor(prot,blue,res);
}

void MainWindow::on_pushButtonResearchAll_clicked()
{
    saveEditor.setItemsAllResearch();
    updateColor();
}

void MainWindow::on_pushButton_clicked()
{
    saveEditor.resetItemsAllResearch();
    updateColor();
}

void MainWindow::on_listWidgetImplant_itemSelectionChanged()
{
    if(!ui->listWidgetImplant->selectedItems().isEmpty()){
        currentItemSelected = ui->listWidgetImplant->selectedItems().first();
        currentRow = ui->listWidgetImplant->row(currentItemSelected);
        currentTable = "listWidgetImplant";
        currentID = implants[currentRow];
        ui->checkBoxPrototype->setChecked(saveEditor.getItemHasPrototype(currentID));
        ui->checkBoxBlueprint->setChecked(saveEditor.getItemHasBlueprints(currentID));
    }
}

void MainWindow::on_listWidgetEquip_itemSelectionChanged()
{
    if(!ui->listWidgetEquip->selectedItems().isEmpty()){
        currentItemSelected = ui->listWidgetEquip->selectedItems().first();
        currentRow = ui->listWidgetEquip->row(currentItemSelected);
        currentTable = "listWidgetEquip";
        currentID = equips[currentRow];
        ui->checkBoxPrototype->setChecked(saveEditor.getItemHasPrototype(currentID));
        ui->checkBoxBlueprint->setChecked(saveEditor.getItemHasBlueprints(currentID));
    }
}

void MainWindow::on_listWidgetWeapon_itemSelectionChanged()
{
    if(!ui->listWidgetWeapon->selectedItems().isEmpty()){
        currentItemSelected = ui->listWidgetWeapon->selectedItems().first();
        currentRow = ui->listWidgetWeapon->row(currentItemSelected);
        currentTable = "listWidgetWeapon";
        currentID = weapon[currentRow];
        ui->checkBoxPrototype->setChecked(saveEditor.getItemHasPrototype(currentID));
        ui->checkBoxBlueprint->setChecked(saveEditor.getItemHasBlueprints(currentID));
    }
}

void MainWindow::on_listWidgetDevice_itemSelectionChanged()
{
    if(!ui->listWidgetDevice->selectedItems().isEmpty()){
        currentItemSelected = ui->listWidgetDevice->selectedItems().first();
        currentRow = ui->listWidgetDevice->row(currentItemSelected);
        currentTable = "listWidgetDevice";
        currentID = devices[currentRow];
        ui->checkBoxPrototype->setChecked(saveEditor.getItemHasPrototype(currentID));
        ui->checkBoxBlueprint->setChecked(saveEditor.getItemHasBlueprints(currentID));
    }
}

void MainWindow::on_listWidgetUndet_itemSelectionChanged()
{
    if(!ui->listWidgetUndet->selectedItems().isEmpty()){
        currentItemSelected = ui->listWidgetUndet->selectedItems().first();
        currentRow = ui->listWidgetUndet->row(currentItemSelected);
        currentTable = "listWidgetUndet";
        currentID = other[currentRow];
        ui->checkBoxPrototype->setChecked(saveEditor.getItemHasPrototype(currentID));
        ui->checkBoxBlueprint->setChecked(saveEditor.getItemHasBlueprints(currentID));
    }
}
