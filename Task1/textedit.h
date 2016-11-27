#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <QtWidgets>

class TextEdit : public QTextEdit
{
    Q_OBJECT
private:
    QPoint m_ptDragPos;

    void startDrag(){
        QMimeData* pMimeData = new QMimeData;
        selectAll();
        pMimeData->setText(this->toPlainText());

        QDrag* pDrag = new QDrag(this);
        pDrag->setMimeData(pMimeData);
        pDrag->setPixmap(QPixmap(":/dragImage.png"));
        pDrag->exec();
    }
protected:
    virtual void mousePressEvent(QMouseEvent* e){
        if(e->button() == Qt::LeftButton){
            m_ptDragPos = e->pos();
        }
        QTextEdit::mousePressEvent(e);
    }

    virtual void mouseMoveEvent(QMouseEvent* e){
        if(e->buttons() & Qt::LeftButton){
            int distance = (e->pos() - m_ptDragPos).manhattanLength();
            if(distance > QApplication::startDragDistance()){
                startDrag();
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
