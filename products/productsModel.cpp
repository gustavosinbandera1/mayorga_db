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

QVariant ProductsModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
//  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
//    if (section == 0) {
//      return QString("Id");
//    } else if (section == 1) {
//      return QString("Description");
//    }else if (section == 2) {
    //      return QString("Price");
    //    }else if (section == 3) {
    //      return QString("Weight");
    //    }
//  }
  return QVariant();
}

int ProductsModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 0;
}

int ProductsModel::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return 2;
}

QVariant ProductsModel::data(const QModelIndex &index, int role) const {
//  if (!index.isValid() || role != Qt::DisplayRole) {
//    return QVariant();
//  }
//  if (index.column() == 0) {
//    return productModel->record(index.row()).value("sku").toString();
//  } else if (index.column() == 1) {
//    return productModel->record(index.row()).value("price").toString();
//  }
  return QVariant();
}
