#include "queryModel.h"

#include <QBrush>
#include <QFont>

QueryModel::QueryModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent) {
  _dbM = dbm;
  _model = new QSqlQueryModel;
}

QVariant QueryModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    if (_headers.count() >= numAvailableHeaders) return _headers[section];
    else return "default";
  }
  (void)section;
  (void)orientation;
  (void)role;
  return QVariant();
}

bool QueryModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role) {
  if (value != headerData(section, orientation, role)) {
    emit headerDataChanged(orientation, section, section);
    return true;
  }
  return false;
}

int QueryModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return _model->rowCount();
}

int QueryModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  return _model->columnCount();
}

QVariant QueryModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  int col = index.column();
  int row = index.row();
  switch (role) {
    case Qt::DisplayRole:
      return _model->record(row).value(col);

    case Qt::FontRole: {
      QFont boldFont;
      // boldFont.setBold(true);
      // boldFont.setWeight(QFont::Bold);
      // boldFont.setPixelSize(18);
      return boldFont;
    } break;
    case Qt::BackgroundRole:
      // return QColor(0,0,0);
      // return QBrush(Qt::blue);
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

bool QueryModel::setData(const QModelIndex &index, const QVariant &value,
                           int role) {
  if (data(index, role) != value) {
    emit dataChanged(index, index, QVector<int>() << role);
    return true;
  }
  return false;
}

Qt::ItemFlags QueryModel::flags(const QModelIndex &index) const {
  if (!index.isValid()) return Qt::NoItemFlags;
  return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void QueryModel::setQuery(const QSqlQuery &query) {
  QSqlQuery query_ = query;
  query_.exec();
  _model->setQuery(query);
  numAvailableHeaders = _model->columnCount();
  qDebug() << "COL COUNT " << _model->columnCount();
}

QSqlQueryModel *QueryModel::updateModel() { lastQuery.exec(); }

void QueryModel::setHeaders(const QStringList headers) { _headers = headers; }
