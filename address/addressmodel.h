#ifndef ADDRESSMODEL_H
#define ADDRESSMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include "dbmanager.h"

class AddressModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit AddressModel(DbManager *dbm, QObject *parent = nullptr);
  QSqlTableModel* updateModel();
  QSqlRelationalTableModel *updateRModel();
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QSqlTableModel *getModel() { return this->addressModel; }
  QSqlRelationalTableModel *getRelationalModel() { return this->addressRelationalModel; }
  void setHeaders(void);
  void setRHeaders(void);

 private:
  DbManager *_dbM;
  QSqlTableModel *addressModel;
  QSqlRelationalTableModel *addressRelationalModel;
};

#endif  // ADDRESSMODEL_H
