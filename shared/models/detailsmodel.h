#ifndef DETAILSMODEL_H
#define DETAILSMODEL_H

#include <QAbstractTableModel>
#include <QSqlQueryModel>

#include "dbmanager.h"

class DetailsModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit DetailsModel(DbManager *dbm, QObject *parent = nullptr);

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  bool setHeaderData(int section, Qt::Orientation orientation,
                     const QVariant &value, int role = Qt::EditRole) override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  // Editable:
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void setQuery(const QSqlQuery& query);
  DetailsModel* getModel() {return this;}
  QSqlQueryModel* updateModel();
  void setHeaders(const QStringList headers);

 private:
  DbManager *_dbM;
  QStringList _headers;
  QSqlQueryModel *_model;
  QSqlQuery lastQuery;
};

#endif  // DETAILSMODEL_H
