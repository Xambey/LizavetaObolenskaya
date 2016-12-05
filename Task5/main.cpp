#include "textedit.h"

int main(int argc, char** argv)
{
    try{
        QApplication app(argc, argv);

        QWidget wgt;
        wgt.resize(400,600);

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
    catch(QException& ex) //обработка ошибок
    {
        QMessageBox M;
        M.setText(QString(ex.what()));
        M.show();
    }
    return 0;
}
