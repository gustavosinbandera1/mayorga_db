#ifndef DETAILSMODEL_H
#define DETAILSMODEL_H

#include <QAbstractTableModel>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include "dbmanager.h"
/**
 * @brief The QueryModel class
 * aims to be just for reads
 * models from this class cannot be edited
 * the reason behinde this behavior is due to
 * "QSqlQueryModel" cannot be alter , but this type of obkects let us
 * do complex queries and inject it into desired tables
 */


class QueryModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit QueryModel(DbManager *dbm, QObject *parent = nullptr);

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

//  // Editable:
//  bool setData(const QModelIndex &index, const QVariant &value,
//               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  void setQuery(const QSqlQuery& query);
  QSqlQueryModel* getModel() {return _model;}
  QSqlQueryModel* updateModel();
  void setHeaders(const QStringList headers);

 private:
  DbManager *_dbM;
  QStringList _headers;
  QSqlQueryModel *_model;
  QSqlQuery lastQuery;
  int numAvailableHeaders;
};

#endif  // DETAILSMODEL_H
