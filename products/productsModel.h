#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

#include "dbmanager.h"
#include <QAbstractTableModel>
#include <QSqlTableModel>

class ProductsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProductsModel(DbManager* dbm, QObject *parent = nullptr);
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QSqlTableModel* getProductModel() { return this->productModel;}

private:
    DbManager *_dbM;
    QSqlTableModel *productModel;
    QList<QString> tm_contact_name;
    QList<QString> tm_contact_phone;

};

#endif // PRODUCTSMODEL_H
