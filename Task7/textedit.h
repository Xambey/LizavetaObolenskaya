#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <QtWidgets>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public slots:
    bool hasDigit(QString s)
    {
        for(QChar c : s) {
            if(c.isDigit())
                return true;
        }
        return false;
    }

    void print(bool)
    {
        QFile file("matrix.xml");
        if(file.open(QIODevice::ReadOnly)) {

            QXmlStreamReader reader(&file); //считывание при помощи Потокового ридера XML
            int sum = 0; //сумма
            int i = 0;
            int end = 0;
            QString text;
            do{
                //говнокод ис детектед
                reader.readNext(); //считываем след. строку
                if(!hasDigit(reader.text().toString()))
                    continue;
                if(i == 0)
                    text += "( ";
                sum += reader.text().toInt(); //добавляем в сумму
                text += reader.text().toString() + " ";
                if(i == 2) {
                    text += ")\n";
                    i = -1;
                }
                i++;
                if(++end == 9)
                    break;

            } while(!reader.atEnd());//пока не конец файла


            text +=  "\nCommon sum: " + QString::number(sum); //вывод общей суммы
            setText(text);
            file.close();
            if(reader.hasError()) { //ошибка!
                setText("Error: " + reader.errorString());
            }
        }
        else
            setText("Файл matrix.xml не найден!");
    }
};

#endif // TEXTEDIT_H
