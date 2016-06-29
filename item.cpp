#include "item.h"

Item::Item()
{

}

Item::Item(QDomElement m_ID, QDomElement m_PlayerHasPrototype, QDomElement m_PlayerHasBlueprints, QDomElement m_ResearchStarted)
{
    this->m_ID = m_ID;
    this->m_PlayerHasBlueprints = m_PlayerHasBlueprints;
    this->m_PlayerHasPrototype = m_PlayerHasPrototype;
    this->m_ResearchStarted = m_ResearchStarted;
}

int Item::getID() const
{
    return m_ID.text().toInt();
}

bool Item::getHasPrototype() const
{
    return m_PlayerHasPrototype.text() == "true" ? true : false;
}

bool Item::getHasBlueprints() const
{
    return m_PlayerHasBlueprints.text() == "true" ? true : false;
}

bool Item::getResearchStarted() const
{
    return m_ResearchStarted.text() == "true" ? true : false;
}

void Item::setHasPrototype(bool status)
{
    m_PlayerHasPrototype.firstChild().setNodeValue(status ? "true" : "false");
}

void Item::setHasBlueprints(bool status)
{
    m_PlayerHasBlueprints.firstChild().setNodeValue(status ? "true" : "false");
}

void Item::setResearchStarted(bool status)
{
    m_ResearchStarted.firstChild().setNodeValue(status ? "true" : "false");
}
