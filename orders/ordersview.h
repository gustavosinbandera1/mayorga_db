#ifndef ORDERSVIEW_H
#define ORDERSVIEW_H

#include <QWidget>
#include "dbmanager.h"
#include "templateModel.h"

class OrdersModel;
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
  CustomModel *oModel;
};

#endif  // ORDERSVIEW_H
