#include "detailsmodel.h"

DetailsModel::DetailsModel(DbManager *dbm, QObject *parent)
    : QAbstractTableModel(parent) {}

QVariant DetailsModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  // FIXME: Implement me!
}

bool DetailsModel::setHeaderData(int section, Qt::Orientation orientation,
                                 const QVariant &value, int role) {
  if (value != headerData(section, orientation, role)) {
    // FIXME: Implement me!
    emit headerDataChanged(orientation, section, section);
    return true;
  }
  return false;
}

int DetailsModel::rowCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  // FIXME: Implement me!
}

int DetailsModel::columnCount(const QModelIndex &parent) const {
  if (parent.isValid()) return 0;

  // FIXME: Implement me!
}

QVariant DetailsModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) return QVariant();

  // FIXME: Implement me!
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

  return Qt::ItemIsEditable;  // FIXME: Implement me!
}
