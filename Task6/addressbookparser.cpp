#include "textedit.h"
#include "addressbookparser.h"

AddressBookParser::AddressBookParser(TextEdit *e, QString num)
{
    letter = num.at(0);
    edit = e;
    finded = false;
}

QString AddressBookParser::printBook(Contact *contact) //печать отдельной книги
{
    QString str;
    str += "Attribute: " + contact->getAttributNumber() + "\n";

    QMap<QString, QString> info = contact->getInformation();
    for(auto i = info.begin(); i != info.end();i++) { //идем по списку данных книги и выводим в консоль
        str += "\tTag name: " + ((QVariant)(i.key())).value<QString>() + "\t Text: " + ((QVariant)(i.value())).value<QString>() + "\n";
    }
    //contact->printed = true; //флаг, книга была напечатана
    finded = true;
    return str;
}

bool AddressBookParser::contactConsist(QString atrNumber) //проверка существования контакта в списке контактов
{
    for(Contact* item : contacts) {
        if(item->getAttributNumber() == atrNumber) //номер совпадает
            return true;
    }
    return false;
}

void AddressBookParser::printBooks() //напечатать контакты по выборкам(по первой букве имени контакта
{
        QString str;
        QStringList l = edit->toPlainText().split("\n");
        for(QString s : l) {
            str += s + "\n";
        }
        str += "Begin selection\n";
        QChar c = letter;
        //QChar c = contact->getInformation().value("name").at(0); //первый символ имени контакта

        for(Contact* t : contacts) { //вывод контакта если первая буква ... совпадает
            if(t->getInformation().value("name").at(0) == c.toLower() || t->getInformation().value("name").at(0) == c.toUpper())
                str += printBook(t);
        }

        str += "End selection\n";
        if(finded)
            edit->setText(str);
        else
            edit->setText("Контакты, с такой первой буквой в имени, не найдены!");
}

bool AddressBookParser::startElement(const QString &, const QString &, const QString &, const QXmlAttributes &atts)
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

bool AddressBookParser::characters(const QString &text)
{
    _text = text;
    return true;
}

bool AddressBookParser::endElement(const QString &, const QString &, const QString &str)
{
    if(str != "contact" && str != "addressbook") { //см 5 задание
        contact->addInfo(str, _text);
    }
    if(!contactConsist(contact->getAttributNumber())) //если контакта ранее не было, добавляем в список контактов
        contacts.append(contact);
    return true;
}

bool AddressBookParser::fatalError(const QXmlParseException &ex)
{
    qDebug() << "Line: " << ex.lineNumber() << "\t Column: " << ex.columnNumber() << "\t Message: " << ex.message();
    return false;
}
