#ifndef PRODUCTSVIEW_H
#define PRODUCTSVIEW_H

#include <QWidget>
#include "dbmanager.h"
#include "spinboxDelegate.h"
#include "comboBoxDelegate.h"
#include "templateModel.h"

class QueryModel;
class ProductsModel;
class LineEditorDelegate;
namespace Ui {
class ProductsView;
}

class ProductsView : public QWidget
{
    Q_OBJECT

public:
    explicit ProductsView(DbManager* dbm, QWidget *parent = nullptr);
    ~ProductsView();
    void updateModel();
    bool isInteger(const QVariant &variant);
    bool isString(const QVariant &variant);

private slots:
    void on_productsView_doubleClicked(const QModelIndex &index);

private:
    Ui::ProductsView *ui;

    SpinboxDelegate *SpinBoxDelegate;
    LineEditorDelegate *lineDelegate;
    ComboBoxDelegate *comboBoxDelegate;

    QueryModel *productModel;
};

#endif // PRODUCTSVIEW_H
