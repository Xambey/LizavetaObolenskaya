#include <QtXml>
#include <QtWidgets>
#include "QMessageBox"

QDomElement makeElement( QDomDocument& domDoc,
                         const QString& strName,
                         const QString& strAttr = QString(),
                         const QString& strText = QString()
        )
{
    QDomElement domElement = domDoc.createElement(strName); //элемент документа в стиле DOM
    //создаем элемент для добавления
    if (!strAttr.isEmpty()) {
        QDomAttr domAttr = domDoc.createAttribute("number");
        domAttr.setValue(strAttr);
        domElement.setAttributeNode(domAttr);
    }
    if (!strText.isEmpty()) {
        QDomText domText = domDoc.createTextNode(strText);
        domElement.appendChild(domText);
    }
    return domElement;
}



QDomElement contact( QDomDocument& domDoc,
                     const QString& strName,
                     const QString& strPhone,
                     const QString& strEmail
                     )
{
    //создаем контакт
    static int nNumber = 1;
    QDomElement domElement = makeElement(domDoc,
                                         "contact",
                                         QString().setNum(nNumber)
                                         );
    //добавляем внутренние теги
    domElement.appendChild(makeElement(domDoc, "name", "", strName));
    domElement.appendChild(makeElement(domDoc, "phone", "", strPhone));
    domElement.appendChild(makeElement(domDoc, "email", "", strEmail));
    nNumber++;
    return domElement;
}

void createXmlDoc() //создаем XML документ
{
    QDomDocument doc("addressbook"); //создать документ
    QDomElement domElement = doc.createElement("addressbook");
    doc.appendChild(domElement); //добавить элемент(тег <addressbook>)

    //контакты
    QDomElement contact1 =
            contact(doc, "Piggy", "+49 631322187", "piggy@mega.de");
    QDomElement contact2 =
            contact(doc, "Kermit", "+49 631322181", "kermit@mega.de");
    QDomElement contact3 =
            contact(doc, "Gonzo", "+49 631322186", "gonzo@mega.de");

    domElement.appendChild(contact1);
    domElement.appendChild(contact2);
    domElement.appendChild(contact3);

    //создаем файл для залива данных
    QFile file("addressbook.xml");
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << doc.toString(); //запись в файл
        file.close();
    }
}

void traverseNode(const QDomNode& node) //меняем xml документ
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                if(domElement.attribute("number") == "1" || "2") {
                    domElement.setAttribute("number","changed");

                }
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling(); //след. элемент
    }
}

int main(int argc, char** argv){
    QApplication app(argc, argv);
    createXmlDoc(); //создаем элемент


    QDomDocument domDoc;
    //файлы, 1й чтение, 2й запись результата
    QFile file("addressbook.xml");
    QFile save("result.xml");

    if(file.open(QIODevice::ReadWrite)) { //открываем в режиме чтения и записи
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement); //обрабатываем элемент
        }

        if(save.open(QIODevice::WriteOnly)) { //открыть(создать) файл в режиме записи
            QTextStream(&save) << domDoc.toString(); //записываем измененные данные
            file.close();
        }

        save.close();
    }

    QMessageBox lbl;
    lbl.setText("XML документ отформатирован!");
    lbl.show();

    return app.exec();
}
