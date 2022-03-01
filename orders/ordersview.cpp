#include <queryModel.h>
#include <QDebug>
#include "ordersmodel.h"
#include "ordersview.h"
#include "ui_ordersview.h"

OrdersView::OrdersView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::OrdersView) {
  ui->setupUi(this);

  orderModel = new QueryModel(dbm, this);
  QSqlQuery query;
  query.prepare(
      "SELECT order_id, payment_type, name, email from orders "
      "JOIN customer ON orders.fk_customer_id=customer.customer_id");

  orderModel->setQuery(query);
  orderModel->setHeaders({"order_id", "payment_type", "name", "email"});
  ui->ordersTableView->setModel(orderModel);

  ui->ordersTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->ordersTableView->horizontalHeader()->setVisible(true);
  ui->ordersTableView->setAlternatingRowColors(true);
  ui->ordersTableView->setSortingEnabled(true);
  ui->ordersTableView->sortByColumn(0, Qt::DescendingOrder);
  ui->ordersTableView->reset();
}
//---------------------
OrdersView::~OrdersView() {
  qDebug() << "Destroying OrdersView";
  delete ui;
}
//---------------------
void OrdersView::updateOrderModel() { orderModel->updateModel(); }
//---------------------
void OrdersView::on_ordersTableView_clicked(const QModelIndex &index) {}
