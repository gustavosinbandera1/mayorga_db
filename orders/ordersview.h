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
  explicit OrdersView(DbManager* dbm, QWidget *parent = nullptr);
  ~OrdersView();
    void updateOrderModel();
    void updateOrderRModel();

private slots:
    void on_ordersTableView_clicked(const QModelIndex &index);

private:
  Ui::OrdersView *ui;
  QueryModel *orderModel;
};

#endif  // ORDERSVIEW_H
