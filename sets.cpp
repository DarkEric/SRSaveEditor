#include "sets.h"
#include <QFile>
#include <QTextStream>

Sets* Sets::pInstance = NULL;

Sets::Sets()
{
    readWeapon();
    readImplants();
    readDevices();
    readEquips();
    readOther();
}

// О боги, что я делаю

void Sets::readWeapon()
{
    QFile file("Wepon.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString str;
    while(!in.atEnd()){
        str = in.readLine();
        QStringList list = str.split(";");
        if(list.size()==2){
            weapons[list.at(0).toInt()]=list.at(1);
        }
    }
    file.close();
}

void Sets::readImplants()
{
    QFile file("Implant.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString str;
    while(!in.atEnd()){
        str = in.readLine();
        QStringList list = str.split(";");
        if(list.size()==2){
            implants[list.at(0).toInt()]=list.at(1);
        }
    }
    file.close();
}

void Sets::readDevices()
{
    QFile file("Device.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString str;
    while(!in.atEnd()){
        str = in.readLine();
        QStringList list = str.split(";");
        if(list.size()==2){
            devices[list.at(0).toInt()]=list.at(1);
        }
    }
    file.close();
}

void Sets::readEquips()
{
    QFile file("Equipment.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString str;
    while(!in.atEnd()){
        str = in.readLine();
        QStringList list = str.split(";");
        if(list.size()==2){
            equips[list.at(0).toInt()]=list.at(1);
        }
    }
    file.close();
}

void Sets::readOther()
{
    QFile file("Other.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString str;
    while(!in.atEnd()){
        str = in.readLine();
        QStringList list = str.split(";");
        if(list.size()==2){
            other[list.at(0).toInt()]=list.at(1);
        }
    }
    file.close();
}

Sets* Sets::getInstance()
{
    if(!pInstance)
    {
        pInstance = new Sets();
    }
    return pInstance;
}
