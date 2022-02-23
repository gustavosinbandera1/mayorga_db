#ifndef ORDERSMODEL_H
#define ORDERSMODEL_H

#include <QAbstractTableModel>
#include <QSqlTableModel>
#include "dbmanager.h"

class OrdersModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit OrdersModel(DbManager *mdb, QObject *parent = nullptr);
    QSqlTableModel* updateModel();
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QSqlTableModel* getOrderModel() { return this->orderModel;}
private:
    DbManager* _dbM;
    QSqlTableModel *orderModel;
    QVariant getItem( int row, int column) const;


};

#endif // ORDERSMODEL_H
