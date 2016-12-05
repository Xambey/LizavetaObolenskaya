#include "textedit.h"

int main(int argc, char** argv)
{

    QApplication app(argc, argv);

    QWidget wgt;
    wgt.resize(500,600);

    QVBoxLayout* layout = new QVBoxLayout(&wgt);

    QLineEdit* line = new QLineEdit;
    TextEdit* edit = new TextEdit(line);

    layout->addWidget(line);
    layout->addWidget(edit);
    wgt.show();

    QObject::connect(line, SIGNAL(textChanged(QString)),edit,SLOT(parserSlot(QString)));
    QObject::connect(line,SIGNAL(selectionChanged()),line,SLOT(clear()));

    return app.exec();

}


//int main()
//{
//    try{ //см. 5 задание
//        Addressbookparser parcer;
//        QFile* file = new QFile("addressbook.xml");

//        QXmlInputSource source(file);
//        QXmlSimpleReader reader;

//        reader.setContentHandler(&parcer);
//        reader.parse(source);

//        parcer.printBooks();
//        return 0;
//    }
//    catch(QException& ex)
//    {
//        qDebug() << ex.what();
//    }
//}
