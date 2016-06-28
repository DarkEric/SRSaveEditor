#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QString"
#include "QDebug"
#include "QSettings"
#include "QStandardPaths"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getFromSaveCurrentMoney()
{
    ui->moneyEdit->setText(QString::number(saveEditor.getCurrentMoney()));
}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation).at(0);
    qDebug()<<path;
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open save"),path+"/SatelliteReign/users/",tr("Save Files (*.xml)"));
    if(!saveEditor.openXML(fileName)) qDebug()<<"Error openXML";
    getFromSaveCurrentMoney();
}
