#include "orderviewer.h"

#include "dbmanager.h"
#include "queryModel.h"
#include "ui_orderviewer.h"

OrderViewer::OrderViewer(DbManager* dbm, QWidget* parent)
    : QDialog(parent), ui(new Ui::OrderViewer) {
  ui->setupUi(this);
  model = new QueryModel(dbm, this);
  sendQuery();

  ui->orderTableViewer->setEnabled(true);
  ui->orderTableViewer->verticalHeader()->setVisible(true);
  ui->orderTableViewer->horizontalHeader()->setVisible(true);
  ui->orderTableViewer->horizontalHeader()->sectionResizeMode(
      QHeaderView::Stretch);

  ui->orderTableViewer->setSortingEnabled(true);
  ui->orderTableViewer->sortByColumn(0, Qt::DescendingOrder);
  ui->orderTableViewer->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

OrderViewer::~OrderViewer() { delete ui; }

void OrderViewer::sendQuery()
{
    QSqlQuery query;
      query.prepare(
          "SELECT num_detail, fk_order_id,fk_product_sku, name from order_detail "
          "JOIN products ON order_detail.fk_product_sku = products.sku");

      model->setQuery(query);
      model->setHeaders({"Id", "Order Id", "Sku", "Name"});
      ui->orderTableViewer->setModel(model);
}
