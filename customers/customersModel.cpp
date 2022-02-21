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

QVariant CustomerModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
  return QVariant();
}

int CustomerModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
    return customerModel->rowCount();
}

int CustomerModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
    return customerModel->columnCount();
}

QVariant CustomerModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole) {
    return QVariant();
  }
  if (index.column() == 0) {
    return customerModel->record(index.row()).value("name").toString();
  } else if (index.column() == 1) {
    return customerModel->record(index.row()).value("email").toString();
  }
  return QVariant();
}
