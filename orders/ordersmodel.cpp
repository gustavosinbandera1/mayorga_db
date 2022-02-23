#include "ordersmodel.h"

OrdersModel::OrdersModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent), _dbM(dbm) {
  orderModel = new QSqlTableModel(this);
  orderModel->setTable("orders");
  orderModel->select();
  orderModel->setHeaderData(0, Qt::Horizontal, "Order_id");
  orderModel->setHeaderData(1, Qt::Horizontal, "Customer_id");
  orderModel->setHeaderData(2, Qt::Horizontal, "Date");
  orderModel->setHeaderData(3, Qt::Horizontal, "Payment");
}
//---------------------
QSqlTableModel *OrdersModel::updateModel() {
  orderModel->setTable("orders");
  orderModel->select();
  return orderModel;
}
//---------------------
QVariant OrdersModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  // FIXME: Implement me!
}
//---------------------
int OrdersModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return orderModel->rowCount();
}
//---------------------
int OrdersModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return orderModel->columnCount();
}
//---------------------
QVariant OrdersModel::getItem(const int row, const int column) const {
  //  switch (column) {
  //    case 0:
  //      return orderModel->record(row).value("sku").toString();
  //    case 1:
  //      return orderModel->record(row).value("description").toString();
  //    case 2:
  //      return orderModel->record(row).value("price").toString();
  //    case 3:
  //      return orderModel->record(row).value("weight").toString();
  //  }
  return QVariant();
}
//---------------------
QVariant OrdersModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  return getItem(index.row(), index.column());
}
