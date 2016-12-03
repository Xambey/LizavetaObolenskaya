#ifndef LISTVIEW_H
#define LISTVIEW_H
#include <QtWidgets>

class TreeView : public QTreeView //переопределенное представление в виде дерева
{
    Q_OBJECT
private:
    QPoint m_ptDragPos; //позиция при перетаскивании

    void startDrag(){
        QMimeData* pMimeData = new QMimeData; //буфер для данных

        //запись текста с модели
        QString data("");
        auto index = this->currentIndex();
        for(int row = 0; row < 3; row++){
            data += " " + index.child(row,0).data().toString();
        }

        pMimeData->setText(data);

        //добавляем картинку
        QDrag* pDrag = new QDrag(this);
        pDrag->setMimeData(pMimeData);
        pDrag->setPixmap(QPixmap(":/dragImage.png"));
        pDrag->exec(); //непосредственный запуск перетаскивания
    }
protected:
    virtual void mousePressEvent(QMouseEvent* e){
        if(e->button() == Qt::LeftButton){ //левая кнопка мыши - нажата
            m_ptDragPos = e->pos(); //запись позиции
        }
        QTreeView::mousePressEvent(e); //отправляем событие дальше
    }

    virtual void mouseMoveEvent(QMouseEvent* e){
        if(e->buttons() & Qt::LeftButton){ //левая кнопка мыши все еще нажата и мышь двигается
            int distance = (e->pos() - m_ptDragPos).manhattanLength();
            if(distance > QApplication::startDragDistance()){
                startDrag(); //запуск перетаскивания
            }
        }
        QTreeView::mousePressEvent(e);
    }

public:
    TreeView(){ //конструктор класса(вызывается при создании объекта
    }
};

#endif // LISTVIEW_H
