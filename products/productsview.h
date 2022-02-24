#ifndef PRODUCTSVIEW_H
#define PRODUCTSVIEW_H

#include <QWidget>
#include "dbmanager.h"
#include "productDelegate.h"
#include "boxdelegate.h"
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
    void updateProductsModel();

    bool isInteger(const QVariant &variant);

    bool isString(const QVariant &variant);

private slots:
    void on_productsView_doubleClicked(const QModelIndex &index);

private:
    Ui::ProductsView *ui;
    ProductsModel* pModel;
    ProductDelegate *productDelegate;
    boxDelegate* boxdelegate;
};

#endif // PRODUCTSVIEW_H
