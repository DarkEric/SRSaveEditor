#ifndef XMLSAVEPARSER_H
#define XMLSAVEPARSER_H

#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QMap>
#include "item.h"

class XMLSaveParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLSaveParser(QObject *parent = 0);
    bool openXML(QString& fileName);
    double getCurrentMoney();
    void setCurrentMoney(double money);
    void saveXML(QString &fileName);

    QList<int> getItemsID();
    bool getItemHasPrototype(int ID);
    bool getItemResearchStarted(int ID);
    bool getItemHasBlueprints(int ID);
    void setItemResearchStarted(int ID, bool status);
    void setItemHasBlueprints(int ID, bool status);
    void setItemHasPrototype(int ID, bool status);
private:
    void parse();
    void parseCurrentMoney();
    void parseItems();

    QDomDocument saveGame;
    QDomElement money;
    QMap<int,Item> items;


signals:

public slots:
};

#endif // XMLSAVEPARSER_H
