#include "ordersview.h"

#include <QDebug>

#include "ordersmodel.h"
#include "ui_ordersview.h"

OrdersView::OrdersView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::OrdersView) {
  ui->setupUi(this);
  bool isRelational = true;
  oModel = new CustomModel(dbm, "orders", isRelational, this);
  oModel->setHeaders({"Id", "Customer_id", "Date", "Payment type"});
  oModel->setRelation(1, "customer", "customer_id", "email");

  ui->ordersTableView->setModel(oModel->getRelationalModel());
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
void OrdersView::updateOrderModel() {
  ui->ordersTableView->setModel(oModel->updateRModel());
   oModel->setHeaders({"Id", "Customer_id", "Date","Payment Type" });
   oModel->setRelation(1, "customer", "customer_id", "email");
}
//---------------------
void OrdersView::on_ordersTableView_clicked(const QModelIndex &index) {
  for (int i = 0; i < oModel->columnCount(); i++) {
    qInfo() << "data " << oModel->index(index.row(), i).data();
  }
}
