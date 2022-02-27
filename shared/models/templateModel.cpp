#include "templateModel.h"

CustomModel::CustomModel(DbManager *dbm, QString table,
                                   bool relational, QObject *parent)
    : QAbstractTableModel(parent) {
  _dbM = dbm;
  _table = table;
  isRelational = relational;
  if (relational) {
      qDebug()<<"Is relational.........";
      relationalModel = new QSqlRelationalTableModel(this);
      relationalModel->setTable(table);
      relationalModel->select();
  } else {
      model = new QSqlTableModel(this);
      model->setTable(table);
      model->select();
  }
}

QSqlTableModel *CustomModel::updateModel() {
    qDebug() << "updating Address model...";
    model->setTable(_table);
    model->select();
    return model;
}

QSqlRelationalTableModel *CustomModel::updateRModel() {
    qDebug()<< "Updating custom Model................******";
    relationalModel->setTable(_table);
    return relationalModel;
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
  if (isRelational)
    return relationalModel->rowCount();
  else
    return model->rowCount();
}
//-------------------
int CustomModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  if (isRelational)
    return relationalModel->columnCount();
  else
    return model->columnCount();
}
//-------------------
QVariant CustomModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  return QVariant();
}
//-------------------
void CustomModel::setHeaders( QStringList &&headers) {
  int i = 0;
  for (const auto &header : headers) {
      qDebug()<< header;
      if (isRelational)
        relationalModel->setHeaderData(i, Qt::Horizontal, header);
      else
        model->setHeaderData(i, Qt::Horizontal, header);
      i++;
  }
}
//-------------------
void CustomModel::setForeignHeaders(QStringList &&headers) {

}

void CustomModel::setRelation(int foreignColumn,QString foreignTable,QString foreignKey,  QString columnToRender ) {
    relationalModel->setTable(_table);
    relationalModel->setRelation(foreignColumn,QSqlRelation(foreignTable, foreignKey, columnToRender));
    //relationalModel->setRelation(0, QSqlRelation("country","country_id","country_name"));
    relationalModel->select();
}
//-------------------
