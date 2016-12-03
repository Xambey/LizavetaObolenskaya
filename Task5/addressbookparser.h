#ifndef ADDRESSBOOKPARSER_H
#define ADDRESSBOOKPARSER_H

#include <QXmlDefaultHandler>
#include <QDebug>
class AddressBookParser : public QXmlDefaultHandler
{
private:
    QString _text;
public:

    virtual bool startElement(const QString &namespaceURI,
                         const QString &localName,
                         const QString &qName,
                         const QXmlAttributes &atts)
    {
        for(int i = 0; i < atts.count(); i++){
            if(atts.localName(i) == "number") {
                qDebug() << "Attribute: " << atts.value(i);
            }
        }
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
            qDebug() << "Tag name: " << str << "\t Text: " << _text;
        }
        return true;
    }

    virtual bool fatalError(const QXmlParseException& ex)
    {
        qDebug() << "Line: " << ex.lineNumber() << "\t Column: " << ex.columnNumber() << "\t Message: " << ex.message();
        return false;
    }
};
#endif // ADDRESSBOOKPARSER_H