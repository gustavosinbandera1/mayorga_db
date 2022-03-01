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
  QSqlRelationalTableModel *updateRModel();
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QSqlTableModel *getModel() { return this->model; }
  void setHeaders(QStringList &&headers);
  void setForeignHeaders(QStringList &&headers);
  void setRelation(int foreignColumn, QString foreignTable, QString foreignKey,
                   QString columnToRender);

 private:
  DbManager *_dbM;
  QSqlTableModel *model;
  QString _table;
};

#endif  // CUSTOMTABLEMODEL_H
