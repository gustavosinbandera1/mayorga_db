#include "orderdetailview.h"
#include "queryModel.h"
#include "readWriteModel.h"
#include "ui_orderdetailview.h"

OrderDetailView::OrderDetailView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::OrderDetailView) {
  ui->setupUi(this);

  _detailModel = new QueryModel(dbm, this);

  QSqlQuery query;

  query.prepare("SELECT num_detail, fk_order_id,fk_product_sku, name from order_detail "
                "JOIN products ON order_detail.fk_product_sku = products.sku");

  _detailModel->setQuery(query);
  _detailModel->setHeaders({"Id", "Order Id", "Sku", "Name"});

  ui->orderDetailTableView->setModel(_detailModel);
  ui->orderDetailTableView->setEnabled(true);
  ui->orderDetailTableView->verticalHeader()->setVisible(true);

  ui->orderDetailTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->orderDetailTableView->horizontalHeader()->setVisible(true);
  ui->orderDetailTableView->setAlternatingRowColors(true);
  ui->orderDetailTableView->setSortingEnabled(true);
  ui->orderDetailTableView->sortByColumn(0, Qt::DescendingOrder);

}

OrderDetailView::~OrderDetailView() { delete ui; }

void OrderDetailView::updateOrderDetailModel() {
  _detailModel->updateModel();
  // ui->orderDetailTableView->setModel(_detailModel);
}
