#include "readWriteModel.h"

#include <QBrush>
#include <QFont>
#include <QTime>

ReadWriteModel::ReadWriteModel(DbManager *dbm, QString table, bool relational,
                               QObject *parent)
    : QAbstractTableModel(parent) {
  _dbM = dbm;
  _table = table;
  model = new QSqlTableModel(this);
  model->setTable(table);
  model->select();

  timer = new QTimer(this);
  timer->setInterval(1000);
  connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
  timer->start();
}
//-------------------
QSqlTableModel *ReadWriteModel::updateModel() {
  qDebug()
      << "............................Updating product model................";
  model->setTable(_table);
  model->select();
  return model;
}
//-------------------
QVariant ReadWriteModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    if (section < headers.count())
      return headers[section];
    else
      return "default";
  }

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

bool ReadWriteModel::setData(const QModelIndex &index, const QVariant &value,
                             int role) {
  qDebug() << "SET DATA WAS CALLED ... " << value;
  model->setData(index, value.toString());
  emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
}
//-------------------
QVariant ReadWriteModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();
  int row = index.row();
  int col = index.column();

  switch (role) {
    case Qt::DisplayRole:
      if (row == 0 && col == 0) return QTime::currentTime().toString();

      return model->index(index.row(), index.column()).data();

    case Qt::EditRole:
      qDebug() << "****************** edit role doing nothing " << index.data();
      return model->data(index);
    case Qt::FontRole: {
      // QFont boldFont;
      // boldFont.setBold(true);
      // boldFont.setWeight(QFont::Bold);
      // boldFont.setPixelSize(18);
      // return boldFont;
      // return QBrush(QColor(0, 255, 0));
    } break;
    case Qt::BackgroundRole:
      if (index.row() % 2) return QBrush(QColor(9, 102, 239, 60));
      // return QColor('red');
      // else
      // return QColor('white');
      return QBrush(QColor(3, 128, 127, 80));
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

Qt::ItemFlags ReadWriteModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
//-------------------
void ReadWriteModel::setHeaders(QStringList &&headers) {
  this->headers = headers;
}
//-------------------
void ReadWriteModel::timerHit() {
  QModelIndex topLeft = createIndex(0, 0);
  emit dataChanged(topLeft, topLeft);
}
