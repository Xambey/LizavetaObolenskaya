#include "addressbookparser.h"
#include <QFile>
#include <QIODevice>
#include <QException>

int main()
{
    try{
        AddressBookParser parcer;
        QFile* file = new QFile("addressbook.xml");

        QXmlInputSource source(file);
        QXmlSimpleReader reader;

        reader.setContentHandler(&parcer);
        reader.parse(source);

        return 0;
    }
    catch(QException& ex)
    {
        qDebug() << ex.what();
    }

}
