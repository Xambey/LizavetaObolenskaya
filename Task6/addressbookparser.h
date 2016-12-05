#ifndef ADDRESSBOOKPARSER_H
#define ADDRESSBOOKPARSER_H
#include <QtXml>
#include <QVector>
#include <QDebug>
#include "contact.h"

class TextEdit;
class AddressBookParser : public QXmlDefaultHandler
{
private:
    TextEdit* edit;
    QString _text; // данные
    QChar letter;
    QString localName;
    bool finded;
    QVector<Contact*> contacts; //вектор(список) контактов
    Contact* contact; //текущий контакт

    QString printBook(Contact* contact);

    bool contactConsist(QString atrNumber) //проверка существования контакта в списке контактов
;

public:

    void printBooks();
    AddressBookParser(TextEdit* e, QString num);

    virtual bool startElement(const QString &namespaceURI,
                         const QString &localName,
                         const QString &qName,
                         const QXmlAttributes &atts);

    virtual bool characters(const QString& text);

    virtual bool endElement(const QString&, const QString&, const QString& str);

    virtual bool fatalError(const QXmlParseException& ex);



};

#endif // ADDRESSBOOKPARSER_H
