int main()
{
    try{
        Addressbookparser parcer;
        QFile* file = new QFile("addressbook.xml");

        QXmlInputSource source(file);
        QXmlSimpleReader reader;

        reader.setContentHandler(&parcer);
        reader.parse(source);

        parcer.printBooks();
        return 0;
    }
    catch(QException& ex)
    {
        qDebug() << ex.what();
    }
}
