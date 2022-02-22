#ifndef PRODUCTSVIEW_H
#define PRODUCTSVIEW_H

#include <QWidget>
#include "dbmanager.h"

class ProductsModel;
namespace Ui {
class ProductsView;
}

class ProductsView : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsView(DbManager* dbm, QWidget *parent = nullptr);
    ~ProductsView();

private slots:
    void on_productsView_clicked(const QModelIndex &index);

private:
    Ui::ProductsView *ui;
    ProductsModel* pModel;
};

#endif // PRODUCTSVIEW_H
