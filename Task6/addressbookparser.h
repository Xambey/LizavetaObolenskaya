#ifndef ADDRESSBOOKPARSER_H
#define ADDRESSBOOKPARSER_H
#include <QtXml>
#include <QVector>
#include <QDebug>
#include "book.h"

class Addressbookparser : public QXmlDefaultHandler
{
private:
    QString _text;
    QVector<Contact*> contacts;
    Contact* contact;

    void printBook(Contact* contact)
    {
        qDebug() << "Attribute: " << contact->getAttributNumber();

        QMap<QString, QString> info = contact->getInformation();
        for(auto i = info.begin(); i != info.end();i++) {
            qDebug() << "Tag name: " << i.key()<< "\t Text: " << i.value();
        }
        contact->printed = true;
    }

    bool contactConsist(QString atrNumber)
    {
        for(Contact* item : contacts) {
            if(item->getAttributNumber() == atrNumber)
                return true;
        }
        return false;
    }

public:

    void printBooks()
    {
        for(Contact* contact : contacts) {
            if(contact->printed) continue;

            qDebug() << "Begin selection\n";
            QChar c = contact->getInformation().value("name").at(0);

            for(Contact* t : contacts) {
                if(t->getInformation().value("name").at(0) == c)
                    printBook(t);
            }
            qDebug() << "End selection\n";
        }
    }

    virtual bool startElement(const QString &namespaceURI,
                         const QString &localName,
                         const QString &qName,
                         const QXmlAttributes &atts)
    {
        if(atts.count() == 0)
            return true;
        if(contactConsist(atts.value(0))) {
            return true;
        }
        contact = new Contact;
        contact->setAttributeNumber(atts.value(0));
        contact->setLocalName(localName);
        return true;
    }

    virtual bool characters(const QString& text)
    {
        _text = text;
        return true;
    }

    virtual bool endElement(const QString&, const QString&, const QString& str)
    {
        if(str != "contact" && str != "addressbook") {
            contact->addInfo(str, _text);
        }
        if(!contactConsist(contact->getAttributNumber()))
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
