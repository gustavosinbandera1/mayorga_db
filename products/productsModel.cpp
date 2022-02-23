#include "productsModel.h"

#include <QSqlTableModel>

ProductsModel::ProductsModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent), _dbM(dbm) {
  productModel = new QSqlTableModel(this);
  productModel->setTable("products");
  productModel->select();
  productModel->setHeaderData(0, Qt::Horizontal, "Id");
  productModel->setHeaderData(1, Qt::Horizontal, "Description");
  productModel->setHeaderData(2, Qt::Horizontal, "Price");
  productModel->setHeaderData(3, Qt::Horizontal, "Weight");
}
//---------------------
QSqlTableModel *ProductsModel::upadateModel()
{
    productModel->setTable("products");
    productModel->select();
    return productModel;
}
//---------------------
QVariant ProductsModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
  return QVariant();
}
//---------------------
int ProductsModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return productModel->rowCount();
}
//---------------------
int ProductsModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return productModel->columnCount();
}
//---------------------
QVariant ProductsModel::getItem(const int row, const int column) const {
  switch (column) {
    case 0:
      return productModel->record(row).value("sku").toString();
    case 1:
      return productModel->record(row).value("description").toString();
    case 2:
      return productModel->record(row).value("price").toString();
    case 3:
      return productModel->record(row).value("weight").toString();
  }
  return QVariant();
}
//---------------------
QVariant ProductsModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || role != Qt::DisplayRole)
    return QVariant();
  return getItem(index.row(), index.column());
}
