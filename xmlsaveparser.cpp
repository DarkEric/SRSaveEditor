#include "xmlsaveparser.h"
#include "QTextStream"

XMLSaveParser::XMLSaveParser(QObject *parent) : QObject(parent)
{

}

bool XMLSaveParser::openXML(QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!saveGame.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();
    parse();
    return true;
}

void XMLSaveParser::setCurrentMoney(double money)
{
    this->money.firstChild().setNodeValue(QString::number(money,'f',2));
}

void XMLSaveParser::saveXML(QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    file.resize(0);
    QTextStream stream(&file);
    stream.setDevice(&file);
    stream << saveGame.toString(-1);
    file.close();
}

void XMLSaveParser::parse()
{
    parseCurrentMoney();
    parseItems();
}

double XMLSaveParser::getCurrentMoney()
{
    return money.text().toDouble();
}

void XMLSaveParser::parseCurrentMoney()
{
    QDomElement root = saveGame.documentElement();
    QDomElement element = root.firstChildElement("m_MoneyManagerSave");
    money = element.firstChildElement("m_PlayersCurrentFunds");
}

void XMLSaveParser::parseItems()
{
    QDomElement root = saveGame.documentElement();
    QDomElement element = root.firstChildElement("m_ItemManager");
    element = element.firstChildElement("m_Items");
    element = element.firstChildElement("SaveItemData");
    while(!element.isNull())
    {
        items.insert(element.firstChildElement("m_ID").text().toInt(),Item(element.firstChildElement("m_ID"),
                             element.firstChildElement("m_PlayerHasPrototype"),
                             element.firstChildElement("m_PlayerHasBlueprints"),
                             element.firstChildElement("m_ResearchStarted")));
        element = element.nextSiblingElement("SaveItemData");
    }
}

QList<int> XMLSaveParser::getItemsID()
{
    return items.keys();
}

bool XMLSaveParser::getItemHasPrototype(int ID)
{
    return items.value(ID).getHasPrototype();
}

bool XMLSaveParser::getItemHasBlueprints(int ID)
{
    return items.value(ID).getHasBlueprints();
}

bool XMLSaveParser::getItemResearchStarted(int ID)
{
    return items.value(ID).getResearchStarted();
}


void XMLSaveParser::setItemHasPrototype(int ID,bool status)
{
    items[ID].setHasPrototype(status);
}

void XMLSaveParser::setItemHasBlueprints(int ID,bool status)
{
    items[ID].setHasBlueprints(status);
}

void XMLSaveParser::setItemResearchStarted(int ID,bool status)
{
    items[ID].setResearchStarted(status);
}

void XMLSaveParser::setItemsAllResearch()
{
    for(auto& i:items)
    {
        i.setHasBlueprints(true);
        i.setResearchStarted(false);
        i.setHasPrototype(false);
    }
}

void XMLSaveParser::resetItemsAllResearch()
{
    for(auto& i:items)
    {
        i.setHasBlueprints(false);
        i.setResearchStarted(false);
        i.setHasPrototype(false);
    }
}
