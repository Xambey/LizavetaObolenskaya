#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <QtWidgets>

class TextEdit : public QTextEdit //наследую все от QTextEdit
{
    //это очень важно, макрос для активации системы сигналов и слотов
    Q_OBJECT
private:
    QPoint m_ptDragPos; //позиция при перемещении

    void startDrag(){
        QMimeData* pMimeData = new QMimeData; //QMimeData это класс для переноса данных
        selectAll();
        pMimeData->setText(this->toPlainText());

        //инициализируем перемещение
        QDrag* pDrag = new QDrag(this);
        pDrag->setMimeData(pMimeData);
        pDrag->setPixmap(QPixmap(":/dragImage.png")); //с картинкой
        pDrag->exec();//создаем событие переноса
    }
protected:
    virtual void mousePressEvent(QMouseEvent* e){ //кнопка нажата
        if(e->button() == Qt::LeftButton){
            m_ptDragPos = e->pos(); //запоминаем позицию
        }
        QTextEdit::mousePressEvent(e); //отправляем дальше
    }

    virtual void mouseMoveEvent(QMouseEvent* e){ //мышка движется
        if(e->buttons() & Qt::LeftButton){ //зажата LKM и все что угодно еще
            int distance = (e->pos() - m_ptDragPos).manhattanLength();
            if(distance > QApplication::startDragDistance()){
                startDrag(); //перенос
            }
        }
        QTextEdit::mousePressEvent(e);
    }

public:
    TextEdit(QString text = "", QWidget* parent = nullptr) :
        QTextEdit(text, parent)
    {
    }
};

#endif // TEXTEDIT_H
