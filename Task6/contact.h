#ifndef BOOK_H
#define BOOK_H
#include <QtXml>
#include <QMap>

class Contact //класс контакт
{
private:
    QMap<QString, QString> info; //словарь <ключ, значение> (имя тега, текст)
    QString atts; //номер атрибута
    QString localName; //имя
public:
    bool printed; //флаг печати
    Contact(){printed = false;} //конструктор создания объекта
    void setAttributeNumber(QString atr)
    {
        atts = atr;
    }
    void addInfo(QString key, QString value) //добавляем инфу
    {
        info.insert(key, value);
    }

    void setLocalName(QString t)
    {
        localName = t;
    }
    QString getAttributNumber() const //получить значение atts
    {
        return atts;
    }
    QString getLocalName() const //получить значение local name
    {
        return localName;
    }
    QMap<QString, QString> getInformation() const//получить список информации
    {
        return info;
    }
};

#endif // BOOK_H
