#include "orderdetailview.h"

#include "detailsmodel.h"
#include "templateModel.h"
#include "ui_orderdetailview.h"

OrderDetailView::OrderDetailView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::OrderDetailView) {
  ui->setupUi(this);

  _detailModel = new DetailsModel(dbm, this);

  QSqlQuery query;
  query.prepare("SELECT city,state, street_number, address_type,name from customer_address "
                "JOIN address ON customer_address.fk_address_id = address.address_id "
                "JOIN customer ON customer_address.fk_customer_id = customer.customer_id");

  _detailModel->setQuery(query);
  _detailModel->setHeaders({"city", "state", "Street", "address_type","name"});

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
