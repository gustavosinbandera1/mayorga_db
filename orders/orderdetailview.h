#ifndef ORDERDETAILVIEW_H
#define ORDERDETAILVIEW_H

#include <QWidget>
#include "dbmanager.h"


class CustomModel;
class DetailsModel;
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

private:
    Ui::OrderDetailView *ui;
    CustomModel *detailModel;
    DetailsModel* _detailModel;
};

#endif // ORDERDETAILVIEW_H
