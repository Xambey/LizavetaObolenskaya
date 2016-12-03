#ifndef ADDRESSBOOKPARSER_H
#define ADDRESSBOOKPARSER_H
#include <QtXml>
#include <QVector>
#include <QDebug>
#include "contact.h"

class Addressbookparser : public QXmlDefaultHandler
{
private:
    QString _text;
    QVector<Contact*> contacts; //вектор(список) контактов
    Contact* contact; //текущий контакт

    void printBook(Contact* contact) //печать отдельной книги
    {
        qDebug() << "\nAttribute: " << contact->getAttributNumber();

        QMap<QString, QString> info = contact->getInformation();
        for(auto i = info.begin(); i != info.end();i++) { //идем по списку данных книги и выводим в консоль
            qDebug() << "\tTag name: " << i.key()<< "\t Text: " << i.value();
        }
        contact->printed = true; //флаг, книга была напечатана
    }

    bool contactConsist(QString atrNumber) //проверка существования контакта в списке контактов
    {
        for(Contact* item : contacts) {
            if(item->getAttributNumber() == atrNumber) //номер совпадает
                return true;
        }
        return false;
    }

public:

    void printBooks() //напечатать контакты с одинаковым именем
    {
        qDebug() << "contacts with the same name\n";
        for(Contact* contact : contacts) {
            if(contact->printed) continue; //если контакт уже печатан, пропускам итерацию

            QString c = contact->getInformation().value("name"); //первый символ имени контакта
            bool finded = false; //есть ли контакты с таким же именем
            for(Contact* t : contacts) { //вывод контакта если имена контактов ... совпадает
                if(t->getInformation().value("name") == c && t != contact){
                    printBook(t);
                    finded = true;
                }
            }
            if(finded) //если есть контакты с таким же именем, то выводим и контакт, для которго искали
                printBook(contact);
        }
    }

    virtual bool startElement(const QString &namespaceURI,
                         const QString &localName,
                         const QString &qName,
                         const QXmlAttributes &atts)
    {
        if(atts.count() == 0) //если атрибутов нет, пропуск
            return true;
        if(contactConsist(atts.value(0))) { //контакт уже существует
            return true;
        }
        contact = new Contact; //создаем объект контакта
        contact->setAttributeNumber(atts.value(0)); //устанавливаем номер атрибута(number="i")
        contact->setLocalName(localName);//локал. имя контакта
        return true;
    }

    virtual bool characters(const QString& text)
    {
        _text = text;
        return true;
    }

    virtual bool endElement(const QString&, const QString&, const QString& str)
    {
        if(str != "contact" && str != "addressbook") { //см 5 задание
            contact->addInfo(str, _text);
        }
        if(!contactConsist(contact->getAttributNumber())) //если контакта ранее не было, добавляем в список контактов
            contacts.append(contact);
        return true;
    }

    virtual bool fatalError(const QXmlParseException& ex)
    {
        qDebug() << "Line: " << ex.lineNumber() << "\t Column: " << ex.columnNumber() << "\t Message: " << ex.message();
        return false;
    }



};

#endif // ADDRESSBOOKPARSER_H
