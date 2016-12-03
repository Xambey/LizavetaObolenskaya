#include "addressbookparser.h"
#include <QFile>
#include <QIODevice>
#include <QException>

int main()
{
    try{
        AddressBookParser parcer; //создаем наш парсер
        QFile* file = new QFile("addressbook.xml");

        QXmlInputSource source(file); //объект источника для парсинга документа
        QXmlSimpleReader reader; //ридер документа

        reader.setContentHandler(&parcer); //устанавливаем обработчик
        reader.parse(source); //запуск парсинга

        return 0;
    }
    catch(QException& ex) //обработка ошибок
    {
        qDebug() << ex.what();
    }

}
