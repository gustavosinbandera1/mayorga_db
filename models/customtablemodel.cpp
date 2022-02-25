#include "customtablemodel.h"

CustomTableModel::CustomTableModel(DbManager* dbm,QString table,bool relational, QObject *parent)
    : QAbstractTableModel(parent)
{
    _dbM = dbm;
    if(relational) {
        model = new QSqlTableModel(this);
        model->setTable(table);
        model->select();
    } else {
        relationalModel = new QSqlRelationalTableModel(this);
        relationalModel->setTable(table);
        relationalModel->select();
    }
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int CustomTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int CustomTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant CustomTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}

void CustomTableModel::setRHeaders(QStringList &&headers)
{
    for(const auto& header: headers) {
        qDebug()<< header ;
    }


   model->setHeaderData(0, Qt::Horizontal, "Id");
   model->setHeaderData(1, Qt::Horizontal, "City");
   model->setHeaderData(2, Qt::Horizontal, "State");
    model->setHeaderData(4, Qt::Horizontal, "Country");
    model->setHeaderData(5, Qt::Horizontal, "Address Type");
}
