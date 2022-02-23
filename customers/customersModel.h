#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

#include <QAbstractTableModel>
#include <QSqlTableModel>

#include "dbmanager.h"

class CustomerModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit CustomerModel(DbManager *dbm, QObject *parent = nullptr);
  QSqlTableModel* updateModel();
    // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QSqlTableModel *getCustomerModel() { return this->customerModel; }

 private:
  DbManager *_dbM;
  QSqlTableModel *customerModel;
  QVariant getItem( int row, int column) const ;
};

#endif  // PRODUCTSMODEL_H
