#ifndef ORDERVIEWER_H
#define ORDERVIEWER_H

#include <QDialog>
#include "dbmanager.h"

class QueryModel;
namespace Ui {
class OrderViewer;
}

class OrderViewer : public QDialog
{
    Q_OBJECT

public:
    explicit OrderViewer(DbManager* dbm, QWidget *parent = nullptr);
    ~OrderViewer();
    void updateModel();
    void sendQuery();

private:
    Ui::OrderViewer *ui;
    QueryModel* model;
    DbManager* _dbM;
};

#endif // ORDERVIEWER_H
