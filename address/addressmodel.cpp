#include "addressmodel.h"

AddressModel::AddressModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent), _dbM(dbm) {
  addressModel = new QSqlTableModel(this);
  addressModel->setTable("address");
  addressModel->select();
  setHeaders();
}

QSqlTableModel *AddressModel::updateModel() {
  qDebug() << "updating Address model...";


  addressModel->setTable("address");
  addressModel->select();
  return addressModel;
}
//---------------------
int AddressModel::rowCount(const QModelIndex &parent) const {
  if (!parent.isValid()) return 0;

  return addressModel->rowCount();
}
//---------------------
int AddressModel::columnCount(const QModelIndex &parent) const {
  if (!parent.isValid()) return 0;
  return addressModel->columnCount();
}
//---------------------
QVariant AddressModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  if (index.column() == 0) {
    return addressModel->record(index.row()).value("street").toString();
  } else if (index.column() == 1) {
    return addressModel->record(index.row()).value("city").toString();
  }
  // FIXME: Implement me!
  return QVariant();
}

void AddressModel::setHeaders() {
  addressModel->setHeaderData(0, Qt::Horizontal, "Id");
  addressModel->setHeaderData(1, Qt::Horizontal, "City");
  addressModel->setHeaderData(2, Qt::Horizontal, "State");
  //addressModel->setHeaderData(3, Qt::Horizontal, "Street & Number"); // this line should have to be hidden when table view rendering data
  addressModel->setHeaderData(4, Qt::Horizontal, "Country");
  addressModel->setHeaderData(5, Qt::Horizontal, "Address Type");
}
//---------------------
QVariant AddressModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  return QVariant();
}
