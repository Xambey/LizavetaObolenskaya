#include <QtWidgets>
#include "textedit.h"

int main(int argc, char**argv){
    QApplication app(argc, argv);

    QWidget wgt;
    wgt.resize(600,600);

    QLabel lbl("нажмите левую кнопку мыши в области редактора текста и не отпуская перетащите текст в документ MS Word");
    TextEdit* edit = new TextEdit("Какой-то текст");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(&lbl);
    layout->addWidget(edit);


    wgt.setLayout(layout);

    wgt.show();

    return app.exec();
}
