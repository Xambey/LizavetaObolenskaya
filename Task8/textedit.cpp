#include "textedit.h"
#include "addressbookparser.h"

void TextEdit::parserSlot(QString)
{
    if(edit->text().isEmpty()){
        setText("Введите имя контакта!");
        return;
    }
    clear();
    AddressBookParser parser(this,edit->text());
    QFile* file = new QFile("addressbook.xml");

    QXmlInputSource source(file); //объект источника для парсинга документа
    QXmlSimpleReader reader; //ридер документа

    reader.setContentHandler(&parser); //устанавливаем обработчик
    reader.parse(source); //запуск парсинга

    parser.printBooks();
}

TextEdit::TextEdit(QLineEdit *edit){
    this->edit = edit;
    setText("Введите имя контакта для поиска");
}
