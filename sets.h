#ifndef SETS_H
#define SETS_H

#include <QMap>
#include <QString>

class Sets
{
public:
    static Sets* getInstance();
    QMap<int, QString> implants;
    QMap<int, QString> weapons;
    QMap<int, QString> devices;
    QMap<int, QString> equips;
    QMap<int, QString> other;
private:
    static Sets* pInstance;
    explicit Sets();
    explicit Sets(const Sets&);
    Sets* operator=(Sets);
    ~Sets();
    void readWeapon();
    void readImplants();
    void readDevices();
    void readEquips();
    void readOther();
};

#endif // SETS_H
