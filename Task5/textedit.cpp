#include "textedit.h"
#include "addressbookparser.h"

void TextEdit::parserSlot(QString)
{
    bool f;
    edit->text().toInt(&f);
    if(!f){
        setText("Введите число!");
        return;
    }
    clear();
    AddressBookParser parser(this,edit->text());
    QFile* file = new QFile("addressbook.xml");

    QXmlInputSource source(file); //объект источника для парсинга документа
    QXmlSimpleReader reader; //ридер документа

    reader.setContentHandler(&parser); //устанавливаем обработчик
    reader.parse(source); //запуск парсинга
    if(!parser.global_finded){
        setText("Контанкт не найден");
    }
}

TextEdit::TextEdit(QLineEdit *edit){
    this->edit = edit;
    setText("Введите номер контакта");
}
