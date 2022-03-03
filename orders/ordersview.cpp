#include <queryModel.h>
#include <QDebug>
#include "ordersview.h"
#include "ui_ordersview.h"

OrdersView::OrdersView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::OrdersView) {
  ui->setupUi(this);
    _dbM = dbm;
  orderModel = new QueryModel(dbm, this);
  sendQuery();

  ui->ordersTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->ordersTableView->horizontalHeader()->setVisible(true);
  ui->ordersTableView->setAlternatingRowColors(true);
  ui->ordersTableView->setSortingEnabled(true);
  ui->ordersTableView->sortByColumn(0, Qt::DescendingOrder);

  ui->ordersTableView->setEditTriggers(
      QAbstractItemView::NoEditTriggers);
  ui->ordersTableView->reset();
}
//----------------------//
//----------------------//
OrdersView::~OrdersView() {
  qDebug() << "Destroying OrdersView";
  delete ui;
}
//----------------------//
//----------------------//
void OrdersView::updateOrderModel() {
    if (orderModel != nullptr) {
      delete orderModel;
      orderModel = new QueryModel(_dbM, this);
    }
    sendQuery();
}
//----------------------//
//----------------------//
void OrdersView::on_ordersTableView_clicked(const QModelIndex &index) {
    int col = index.column();
    int row = index.row();

}
//----------------------//
//----------------------//
void OrdersView::sendQuery()
{
    QSqlQuery query;
    query.prepare(
        "SELECT order_id, payment_type, name, email from orders "
        "JOIN customer ON orders.fk_customer_id=customer.customer_id");

    orderModel->setQuery(query);
    orderModel->setHeaders({"order_id", "payment_type", "name", "email"});
    ui->ordersTableView->setModel(orderModel);
}

void OrdersView::on_ordersTableView_doubleClicked(const QModelIndex &index)
{
    int col = index.column();
    int row = index.row();
    auto reg = orderModel->getModel()->record(row);
    QString order_id =  reg.value("order_id").toString();
    qDebug()<<"OrderID: "<< order_id;


}
