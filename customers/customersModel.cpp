#include "customersModel.h"

#include <QSqlTableModel>

CustomerModel::CustomerModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent), _dbM(dbm) {
  customerModel = new QSqlTableModel(this);
  customerModel->setTable("customer");
  customerModel->select();
  // columns names overwritten
  customerModel->setHeaderData(1, Qt::Horizontal, "Name");
  customerModel->setHeaderData(2, Qt::Horizontal, "Email");
  customerModel->setHeaderData(3, Qt::Horizontal, "Phone");
  customerModel->setHeaderData(4, Qt::Horizontal, "Password");
}
//---------------------
QSqlTableModel *CustomerModel::updateModel()
{
    customerModel->setTable("customer");
    customerModel->select();
    return customerModel;
}
//---------------------
QVariant CustomerModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
  return QVariant();
}
//---------------------
int CustomerModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return customerModel->rowCount();
}
//---------------------
int CustomerModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return customerModel->columnCount();
}
//---------------------
QVariant CustomerModel::getItem(const int row, const int column) const {
  switch (column) {
    case 0:
      return customerModel->record(row).value("customer_id").toString();
    case 1:
      return customerModel->record(row).value("name").toString();
    case 2:
      return customerModel->record(row).value("email").toString();
    case 3:
      return customerModel->record(row).value("phone").toString();
    case 4:
      return customerModel->record(row).value("password").toString();
  }
  return QVariant();
}
//---------------------
QVariant CustomerModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) {
    return QVariant();
  }
  return getItem(index.row(), index.column());
}
//---------------------
