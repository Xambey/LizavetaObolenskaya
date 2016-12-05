#include <QtXml>
#include "textedit.h"
int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QWidget wgt;
    wgt.resize(400,600);

    TextEdit edit;
    QPushButton button("Обновить");
    QVBoxLayout* layout = new QVBoxLayout(&wgt);

    layout->addWidget(&edit);
    layout->addWidget(&button);

    QObject::connect(&button, SIGNAL(clicked(bool)), &edit, SLOT(print(bool)));

    wgt.show();


    return app.exec();
}
