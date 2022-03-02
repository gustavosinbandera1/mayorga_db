#include "readWriteModel.h"

ReadWriteModel::ReadWriteModel(DbManager *dbm, QString table, bool relational,
                               QObject *parent)
    : QAbstractTableModel(parent) {
  _dbM = dbm;
  _table = table;
  model = new QSqlTableModel(this);
  model->setTable(table);
  model->select();
}
//-------------------
QSqlTableModel *ReadWriteModel::updateModel() {
  model->setTable(_table);
  model->select();
  return model;
}
//-------------------
QVariant ReadWriteModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  (void)section;
  (void)orientation;
  (void)role;
  return QVariant();
}
//-------------------
int ReadWriteModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;
  return model->rowCount();
}
//-------------------
int ReadWriteModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;
  return model->columnCount();
}

//bool ReadWriteModel::setData(const QModelIndex &index, const QVariant &value,
//                             int role) {

//}
//-------------------
QVariant ReadWriteModel::data(const QModelIndex &index, int role) const {
  qDebug() << "THIS WILL NEED TO BE IMPLEMENTED .....";
    if (!index.isValid()) return QVariant();
     return model->index(index.row(), index.column()).data();
}
//-------------------
void ReadWriteModel::setHeaders(QStringList &&headers) {
  int i = 0;
  for (const auto &header : headers) {
    model->setHeaderData(i, Qt::Horizontal, header);
    i++;
  }
}
//-------------------
void ReadWriteModel::setForeignHeaders(QStringList &&headers) {}
