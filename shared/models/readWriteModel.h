#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractItemModel>
#include <QAbstractTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>

#include "dbmanager.h"

class ReadWriteModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit ReadWriteModel(DbManager *dbm, QString table, bool relational,
                       QObject *parent = nullptr);

  QSqlTableModel *updateModel();
  QSqlTableModel *getModel() {return model;}
  //QSqlRelationalTableModel *updateRModel();
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  //bool setData(const QModelIndex &index, const QVariant &value, int role);

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  void setHeaders(QStringList &&headers);
  void setForeignHeaders(QStringList &&headers);
  void setRelation(int foreignColumn, QString foreignTable, QString foreignKey,
                   QString columnToRender);
 private:
  DbManager *_dbM;
  QSqlTableModel *model;
  QString _table;

  // QAbstractItemModel interface

};

#endif  // CUSTOMTABLEMODEL_H
