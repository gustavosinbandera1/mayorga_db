#ifndef ORDERDETAILVIEW_H
#define ORDERDETAILVIEW_H

#include <QWidget>
#include "dbmanager.h"

class QueryModel;
namespace Ui {
class OrderDetailView;
}

class OrderDetailView : public QWidget
{
    Q_OBJECT

public:
    explicit OrderDetailView(DbManager* dbm, QWidget *parent = nullptr);
    ~OrderDetailView();
    void updateOrderDetailModel();
    void sendQuery();

private:
    Ui::OrderDetailView *ui;
    QueryModel* _detailModel;
    DbManager* _dbM;
};

#endif // ORDERDETAILVIEW_H
