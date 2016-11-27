#include <QtWidgets>
#include "treeview.h"

int main(int argc, char**argv){
    QApplication app(argc, argv);

    QWidget wgt;
    wgt.resize(600,600);

    QLabel lbl("нажмите левую кнопку мыши по элементу(1,2 или 3) и не отпуская перетащите текст группы элементов в документ MS Word");

    QStandardItemModel model(3,1);

    int inRow = 0;
    for(int TopRow = 0; TopRow < 3; TopRow++){
        QModelIndex index = model.index(TopRow,0);
        model.setData(index, "элемент " + QString::number(TopRow + 1));
        model.insertRows(0,3,index);
        model.insertColumns(0,1,index);
        for(int row = 0; row < 3; row++, inRow++){
            model.setData(model.index(row,0,index),"строка " + QString::number(inRow + 1));
        }
    }


    TreeView* view = new TreeView;
    view->setModel(&model);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(&lbl);
    layout->addWidget(view);


    wgt.setLayout(layout);

    wgt.show();

    return app.exec();
}
