#include <QtXml>
int main()
{
    QFile file("matrix.xml");
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader reader(&file);
        int sum = 0;
        do{
            reader.readNext();
            sum += reader.text().toInt();
        } while(!reader.atEnd());

        if(reader.hasError()) {
            qDebug() << "Error: " << reader.errorString();
        }
        qDebug() << "Common sum: " << sum;
        file.close();
    }
    return 0;
}
