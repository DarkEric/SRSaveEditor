#ifndef ITEM_H
#define ITEM_H

#include <QDomElement>

class Item
{
public:
    Item();
    Item(QDomElement m_ID,
        QDomElement m_PlayerHasPrototype,
        QDomElement m_PlayerHasBlueprints,
        QDomElement m_ResearchStarted);


    int getID() const;
    bool getHasPrototype() const;
    bool getHasBlueprints() const;
    bool getResearchStarted() const;
    void setHasPrototype(bool status);
    void setHasBlueprints(bool status);
    void setResearchStarted(bool status);
private:
    QDomElement m_ID;
    QDomElement m_PlayerHasPrototype;
    QDomElement m_PlayerHasBlueprints;
    QDomElement m_ResearchStarted;
};

#endif // ITEM_H
