#include <QtWidgets>
#include "treeview.h"

int main(int argc, char**argv){
    QApplication app(argc, argv);

    QWidget wgt;
    wgt.resize(600,600); //устанавливаем размер виджета

    QLabel lbl("нажмите левую кнопку мыши по элементу(1,2 или 3) и не отпуская перетащите текст группы внутренних элементов в документ MS Word");

    QStandardItemModel model(3,1); //создаем модель из трех строк и 1 столбца

    //забиваем данные
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

    //создаем представление для модели
    TreeView* view = new TreeView;
    view->setModel(&model);
    view->setSelectionMode(QAbstractItemView::SingleSelection); //одиночное выделение элементов
    view->setDragEnabled(true); //разрешение на перетаскивание
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true); //картинка разрешена

    QVBoxLayout* layout = new QVBoxLayout; //создаем вертикальный слой для виджетов

    //добавляем элементы на слой
    layout->addWidget(&lbl);
    layout->addWidget(view);

    //устанавливаем слой для виджета
    wgt.setLayout(layout);

    wgt.show();

    return app.exec();
}
