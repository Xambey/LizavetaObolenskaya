#include <QtXml>
#include <QtWidgets>


QDomElement makeElement( QDomDocument& domDoc,
                         const QString& strName,
                         const QString& strAttr = QString(),
                         const QString& strText = QString()
        )
{
    QDomElement domElement = domDoc.createElement(strName);
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
    static int nNumber = 1;
    QDomElement domElement = makeElement(domDoc,
                                         "contact",
                                         QString().setNum(nNumber)
                                         );
    domElement.appendChild(makeElement(domDoc, "name", "", strName));
    domElement.appendChild(makeElement(domDoc, "phone", "", strPhone));
    domElement.appendChild(makeElement(domDoc, "email", "", strEmail));
    nNumber++;
    return domElement;
}

void createXmlDoc()
{
    QDomDocument doc("addressbook");
    QDomElement domElement = doc.createElement("addressbook");
    doc.appendChild(domElement);

    QDomElement contact1 =
            contact(doc, "Piggy", "+49 631322187", "piggy@mega.de");
    QDomElement contact2 =
            contact(doc, "Kermit", "+49 631322181", "kermit@mega.de");
    QDomElement contact3 =
            contact(doc, "Gonzo", "+49 631322186", "gonzo@mega.de");

    domElement.appendChild(contact1);
    domElement.appendChild(contact2);
    domElement.appendChild(contact3);

    QFile file("addressbook.xml");
    if(file.open(QIODevice::WriteOnly)) {
        QTextStream(&file) << doc.toString();
        file.close();
    }
}

void traverseNode(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                if(domElement.tagName() == "contact") { //меняем теги
                    domElement.setTagName("ChangedTag");
                }
            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

int main(int argc, char** argv){
    QApplication app(argc, argv);
    //см комменты из 3 задания
    createXmlDoc();


    QDomDocument domDoc;
    QFile file("addressbook.xml");
    if(file.open(QIODevice::ReadWrite)) {
        if(domDoc.setContent(&file)) {
            QDomElement domElement= domDoc.documentElement();
            traverseNode(domElement);
        }
        file.close();

        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) //открыть в режиме записи и режиме усечения(редактирования)
            QTextStream(&file) << domDoc.toString();
        file.close();

    }

    QMessageBox lbl;
    lbl.setText("XML документ отредактирован!");
    lbl.show();

    return app.exec();
}
