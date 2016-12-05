#include "addressbookparser.h"
#include "textedit.h"
AddressBookParser::AddressBookParser(TextEdit *e, QString num)
{
    number = num.toInt();
    edit = e;
    finded = false;
}

bool AddressBookParser::startElement(const QString &, const QString &, const QString&, const QXmlAttributes &atts) //атрибуты документа
{
    for(int i = 0; i < atts.count(); i++){
        if(atts.value(i) == QString::number(number)) {
            edit->setText(edit->toPlainText() + "\nAttribute: " + atts.value(i));
            finded = true;
            global_finded = true;
        }
    }
    return true;
}

bool AddressBookParser::characters(const QString &text)
{
    _text = text;
    return true;
}

bool AddressBookParser::endElement(const QString &, const QString &, const QString &str)
{
    if(str != "contact" && str != "addressbook" && finded) { //не обрабатываем /contact, /addressbook
        QStringList l = edit->toPlainText().split("\n");
        QString s;
        for(QString t: l) {
            s += t + "\n";
        }
        if(str == "email") {
            finded = false;
            edit->setText(s + "\nTag name: " + str + "\t Text: " + _text + "\n");
        }
        else {
            edit->setText(s + "\nTag name: " + str + "\t Text: " + _text);
        }
    }
    return true;
}

bool AddressBookParser::fatalError(const QXmlParseException &ex) //обработка исключительных ситуаций
{
    qDebug() << "Line: " << ex.lineNumber() << "\t Column: " << ex.columnNumber() << "\t Message: " << ex.message();
    return false;
}
