#include <QtWidgets>
#include "textedit.h"

int main(int argc, char**argv){
    QApplication app(argc, argv);

    QWidget wgt;
    wgt.resize(600,600);

    //надпись
    QLabel lbl("нажмите левую кнопку мыши в области редактора текста и не отпуская перетащите текст в документ MS Word");

    //текстовый редактор
    TextEdit* edit = new TextEdit("Какой-то текст");

    //вертикальный слой, на который я добавляю виджеты lbl и edit
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(&lbl);
    layout->addWidget(edit);

    //установка слоя на виджет
    wgt.setLayout(layout);

    wgt.show();

    return app.exec();
}
