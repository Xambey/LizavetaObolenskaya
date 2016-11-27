#ifndef LISTVIEW_H
#define LISTVIEW_H
#include <QtWidgets>

class TreeView : public QTreeView
{
    Q_OBJECT
private:
    QPoint m_ptDragPos;

    void startDrag(){
        QMimeData* pMimeData = new QMimeData;

        QString data("");
        auto index = this->currentIndex();
        for(int row = 0; row < 3; row++){
            data += " " + index.child(row,0).data().toString();
        }

        pMimeData->setText(data);

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
        QTreeView::mousePressEvent(e);
    }

    virtual void mouseMoveEvent(QMouseEvent* e){
        if(e->buttons() & Qt::LeftButton){
            int distance = (e->pos() - m_ptDragPos).manhattanLength();
            if(distance > QApplication::startDragDistance()){
                startDrag();
            }
        }
        QTreeView::mousePressEvent(e);
    }

public:
    TreeView(){
    }
};

#endif // LISTVIEW_H
