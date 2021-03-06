#ifndef PRODUCTSVIEW_H
#define PRODUCTSVIEW_H

#include <QWidget>

#include "comboBoxDelegate.h"
#include "dbmanager.h"
#include "productsdto.h"
#include "spinboxDelegate.h"
//#include "readWriteModel.h"

class ReadWriteModel;
class LineEditorDelegate;
namespace Ui {
class ProductsView;
}

class ProductsView : public QWidget {
  Q_OBJECT

 public:
  explicit ProductsView(DbManager *dbm, QWidget *parent = nullptr);
  ~ProductsView();
  void updateModel();
  bool isInteger(const QVariant &variant);
  bool isString(const QVariant &variant);

 private slots:
  void on_productsView_doubleClicked(const QModelIndex &index);
  void on_updateButton_clicked();
  void on_deleteButton_clicked();
  void on_newButton_clicked();
  void on_productsView_clicked(const QModelIndex &index);

 private:
  Ui::ProductsView *ui;
  DbManager *_dbM;
  SpinboxDelegate *SpinBoxDelegate;
  LineEditorDelegate *lineDelegate;
  ComboBoxDelegate *comboBoxDelegate;
  ReadWriteModel *productModel;
  ProductDataObject product;
};

#endif  // PRODUCTSVIEW_H
