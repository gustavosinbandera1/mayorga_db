#include "templateModel.h"

CustomModel::CustomModel(DbManager *dbm, QString table, bool relational,
                         QObject *parent)
    : QAbstractTableModel(parent) {
  _dbM = dbm;
  _table = table;
  model = new QSqlTableModel(this);
  model->setTable(table);
  model->select();
}

QSqlTableModel *CustomModel::updateModel() {
  model->setTable(_table);
  model->select();
  return model;
}
//-------------------
QVariant CustomModel::headerData(int section, Qt::Orientation orientation,
                                 int role) const {
  (void)section;
  (void)orientation;
  (void)role;
  return QVariant();
}
//-------------------
int CustomModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;
  return model->rowCount();
}
//-------------------
int CustomModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;
  return model->columnCount();
}
//-------------------
QVariant CustomModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  return model->index(index.row(), index.column()).data();
}
//-------------------
void CustomModel::setHeaders(QStringList &&headers) {
  qDebug() << "THIS WILL NEED TO BE IMPLEMENTED .....";
  int i = 0;
  for (const auto &header : headers) {
    model->setHeaderData(i, Qt::Horizontal, header);
    i++;
  }
}
//-------------------
void CustomModel::setForeignHeaders(QStringList &&headers) {}
