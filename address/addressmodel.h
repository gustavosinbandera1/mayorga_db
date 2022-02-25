#ifndef ADDRESSMODEL_H
#define ADDRESSMODEL_H

#include <QAbstractItemModel>
#include <QSqlTableModel>

#include "dbmanager.h"

class AddressModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit AddressModel(DbManager *dbm, QObject *parent = nullptr);
  QSqlTableModel* updateModel();
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QSqlTableModel *getAddressModel() { return this->addressModel; }
  void setHeaders(void);

 private:
  DbManager *_dbM;
  QSqlTableModel *addressModel;
};

#endif  // ADDRESSMODEL_H
