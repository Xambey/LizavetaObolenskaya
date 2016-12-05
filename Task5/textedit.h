#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <QtWidgets>
#include <QtXml>

class TextEdit : public QTextEdit
{
    Q_OBJECT
private:
    QLineEdit* edit;
public:
    TextEdit(QLineEdit* edit);
public slots:
    void parserSlot(QString);
};

#endif // TEXTEDIT_H
