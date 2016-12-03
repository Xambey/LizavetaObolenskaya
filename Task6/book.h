#ifndef BOOK_H
#define BOOK_H
#include <QtXml>
#include <QMap>

class Contact
{
private:
    QMap<QString, QString> info; //словарь <ключ, значение> (имя тега, текст)
    QString atts;
    QString localName;
public:
    bool printed;
    Contact(){printed = false;}
    void setAttributeNumber(QString atr)
    {
        atts = atr;
    }
    void addInfo(QString key, QString value)
    {
        info.insert(key, value);
    }

    void setLocalName(QString t)
    {
        localName = t;
    }
    QString getAttributNumber() const
    {
        return atts;
    }
    QString getLocalName() const
    {
        return localName;
    }
    QMap<QString, QString> getInformation() const
    {
        return info;
    }
};

#endif // BOOK_H
