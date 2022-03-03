#include "readWriteModel.h"

#include <QBrush>
#include <QFont>

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
    if (!index.isValid()) return QVariant();
    switch (role) {
     case Qt::DisplayRole:
        return model->index(index.row(), index.column()).data();


    case Qt::EditRole :
      qDebug()<<"****************** edit role ";

    case Qt::FontRole: {
      QFont boldFont;
       boldFont.setBold(true);
       //boldFont.setWeight(QFont::Bold);
       //boldFont.setPixelSize(18);
      //return boldFont;
       //return QBrush(QColor(0, 255, 0));
    } break;
    case Qt::BackgroundRole:
      if(index.row()%2)
        return QBrush(QColor(9,102,239,60));
          //return QColor('red');
      //else
       //return QColor('white');
       return QBrush(QColor(3,128,127,80));
      break;
    case Qt::TextAlignmentRole:
      return int(Qt::AlignCenter | Qt::AlignVCenter);
      break;
    case Qt::CheckStateRole:
      // return Qt::Checked;
      break;



   }
    return QVariant();
}

Qt::ItemFlags ReadWriteModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
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
