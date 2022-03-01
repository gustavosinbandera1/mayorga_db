#include "detailsmodel.h"

#include <QBrush>
#include <QFont>

DetailsModel::DetailsModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent) {
  _dbM = dbm;
  _detailModel = new QSqlQueryModel;
}

QVariant DetailsModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return _headers[section];
  }
  (void)section;
  (void)orientation;
  (void)role;
  return QVariant();
}

bool DetailsModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role) {
  if (value != headerData(section, orientation, role)) {
    emit headerDataChanged(orientation, section, section);
    return true;
  }
  return false;
}

int DetailsModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return _detailModel->rowCount();
}

int DetailsModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return _detailModel->columnCount();
}

QVariant DetailsModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int col = index.column();
  int row = index.row();
  switch (role) {
    case Qt::DisplayRole:
      return _detailModel->record(row).value(col);

    case Qt::FontRole:
      {
        QFont boldFont;
        //boldFont.setBold(true);
        //boldFont.setWeight(QFont::Bold);
        //boldFont.setPixelSize(18);
        return boldFont;
      }
      break;
    case Qt::BackgroundRole:
     // return QColor(0,0,0);
        //return QBrush(Qt::blue);
      break;
    case Qt::TextAlignmentRole:
        return int(Qt::AlignCenter | Qt::AlignVCenter);
      break;
    case Qt::CheckStateRole:
        //return Qt::Checked;
      break;
  }
  return QVariant();
}

bool DetailsModel::setData(const QModelIndex &index, const QVariant &value,
                           int role) {
  if (data(index, role) != value) {
    // FIXME: Implement me!
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
  }
  return false;
}

Qt::ItemFlags DetailsModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void DetailsModel::setQuery(const QString &query) {
  _detailModel->setQuery(query);
}

QSqlQueryModel *DetailsModel::updateModel() {


}

void DetailsModel::setHeaders(const QStringList headers)
{
    _headers = headers;
}
