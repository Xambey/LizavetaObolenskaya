#ifndef ADDRESSBOOKPARSER_H
#define ADDRESSBOOKPARSER_H

#include <QXmlDefaultHandler>
#include <QDebug>
#include <QtWidgets>
#include <QException>
#include <QMessageBox>

class TextEdit;
class AddressBookParser : public QXmlDefaultHandler
{
private:
    TextEdit* edit;
    QString _text; // данные
    int number;
    bool finded;
public:
    bool global_finded;
    AddressBookParser(TextEdit* e, QString num);
    //переопределенные методы, расположены в порядке вызова
    virtual bool startElement(const QString &namespaceURI,
                         const QString &localName,
                         const QString &qName,
                         const QXmlAttributes &atts);

    virtual bool characters(const QString& text);

    virtual bool endElement(const QString&, const QString&, const QString& str);

    virtual bool fatalError(const QXmlParseException& ex);
};
#endif // ADDRESSBOOKPARSER_H
