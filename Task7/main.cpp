#include <QtXml>
int main()
{
    QFile file("matrix.xml");
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader reader(&file); //считывание при помощи Потокового ридера XML
        int sum = 0; //сумма
        do{
            reader.readNext(); //считываем след. строку
            sum += reader.text().toInt(); //добавляем в сумму
        } while(!reader.atEnd());//пока не конец файла

        if(reader.hasError()) { //ошибка!
            qDebug() << "Error: " << reader.errorString();
        }
        qDebug() << "Common sum: " << sum; //вывод общей суммы
        file.close();
    }
    return 0;
}
