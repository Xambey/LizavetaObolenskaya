#include "textedit.h"
#include "addressbookparser.h"

void TextEdit::parserSlot(QString)
{
    bool f;

    if(!(edit->text().count() == 1)){
        setText("Введите одну латинскую букву!");
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
    setText("Введите первую букву имени контактов, для которых нужно сделать выборку");
}
