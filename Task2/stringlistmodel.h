#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H
#include <QtWidgets>

class StringListModel : public QStringListModel
{
    Q_OBJECT
protected:
    virtual Qt::DropAction supportedDragActions() const
    {
        return Qt::CopyAction | Qt::MoveAction;
    }

     virtual Qt::ItemFlags DragDropListModel::flags(const QModelIndex &index) const
     {
         Qt::ItemFlags defaultFlags = QStringListModel::flags(index);

         if (index.isValid())
             return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
         else
             return Qt::ItemIsDropEnabled | defaultFlags;
     }

public:
    StringListModel();
};

#endif // STRINGLISTMODEL_H
