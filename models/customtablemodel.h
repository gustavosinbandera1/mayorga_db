#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>

#include <QAbstractItemModel>
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include "dbmanager.h"

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CustomTableModel(DbManager *dbm, QString table,bool relational,  QObject *parent = nullptr);

    QSqlTableModel* updateModel();
    QSqlRelationalTableModel *updateRModel();
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    QSqlTableModel *getModel() { return this->model; }
    QSqlRelationalTableModel *getRelationalModel() { return this->relationalModel; }
    void setHeaders(void);
    void setRHeaders(QStringList &&headers);

   private:
    DbManager *_dbM;
    QSqlTableModel *model;
    QSqlRelationalTableModel *relationalModel;
};

#endif // CUSTOMTABLEMODEL_H
