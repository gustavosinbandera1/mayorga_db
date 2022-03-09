#ifndef ORDERSVIEW_H
#define ORDERSVIEW_H

#include <QWidget>

#include "dbmanager.h"
#include "readWriteModel.h"

class QueryModel;
namespace Ui {
class OrdersView;
}

class OrdersView : public QWidget {
  Q_OBJECT

 public:
  explicit OrdersView(DbManager *dbm, QWidget *parent = nullptr);
  ~OrdersView();
  void updateOrderModel();
  // void updateOrderRModel();

 private slots:
  void on_ordersTableView_clicked(const QModelIndex &index);

  void on_ordersTableView_doubleClicked(const QModelIndex &index);

 private:
  Ui::OrdersView *ui;
  QueryModel *orderModel;
  DbManager *_dbM;
  void sendQuery();
};

#endif  // ORDERSVIEW_H
