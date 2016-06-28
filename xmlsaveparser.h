#ifndef XMLSAVEPARSER_H
#define XMLSAVEPARSER_H

#include <QObject>
#include <QDomDocument>
#include <QFile>

class XMLSaveParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLSaveParser(QObject *parent = 0);
    bool openXML(QString& fileName);
    double getCurrentMoney();

private:
    QDomDocument saveGame;

signals:

public slots:
};

#endif // XMLSAVEPARSER_H
