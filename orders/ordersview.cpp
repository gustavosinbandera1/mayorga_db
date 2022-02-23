#include "ordersview.h"

#include <QDebug>

#include "ordersmodel.h"
#include "ui_ordersview.h"

OrdersView::OrdersView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::OrdersView) {
  ui->setupUi(this);
  oModel = new OrdersModel(dbm, this);
  ui->ordersTableView->setModel(oModel->getOrderModel());
  ui->ordersTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->ordersTableView->horizontalHeader()->setVisible(true);
  ui->ordersTableView->setAlternatingRowColors(true);
}
//---------------------
OrdersView::~OrdersView() {
  qDebug() << "Destroying OrdersView";
  delete ui;
}
//---------------------
void OrdersView::updateOrderModel() {
  ui->ordersTableView->setModel(oModel->updateModel());
}
//---------------------
void OrdersView::on_ordersTableView_clicked(const QModelIndex &index) {
  for (int i = 0; i < oModel->columnCount(); i++) {
    qInfo() << "data " << oModel->index(index.row(), i).data();
  }
}
