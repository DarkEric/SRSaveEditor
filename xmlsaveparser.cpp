#include "xmlsaveparser.h"

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
    return true;
}

double XMLSaveParser::getCurrentMoney()
{
    QDomElement docElem = saveGame.documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()&&e.tagName()=="m_MoneyManagerSave")
        {
            n = e.firstChild();
            continue;
        }
        if(!e.isNull()&&e.tagName()=="m_PlayersCurrentFunds")
        {
            return e.text().toDouble();
        }
        n = n.nextSibling();
    }
    return 0;
}
