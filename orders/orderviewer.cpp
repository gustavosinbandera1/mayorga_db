#include "orderviewer.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "ui_orderviewer.h"

OrderViewer::OrderViewer(DbManager* dbm, int orderId, QWidget* parent)
    : QDialog(parent), ui(new Ui::OrderViewer) {
  ui->setupUi(this);
  _dbM = dbm;
  orderID = orderId;
  qDebug() << "Receiving parameter " << orderId;
  connect(ui->okButton, SIGNAL(&clicked()), this, SLOT(close()));
  model = new QueryModel(dbm, this);
  sendQuery();

  //     q.clear();
  //    q.exec(QString(
  //        "select sku, quantity , order_id, order_detail.price,   sum(quantity
  //        * " "order_detail.price)  AS subTotal  " "from order_detail " " JOIN
  //        orders ON " "order_detail.fk_order_id=orders.order_id " "JOIN
  //        products ON " "order_detail.fk_product_sku=products.sku where
  //        order_id = 1 GROUP BY " "sku,quantity,orders.order_id,
  //        order_detail.price "

  //      ));
}

OrderViewer::~OrderViewer() { delete ui; }

void OrderViewer::sendQuery() {
  QSqlQuery query;
  query.prepare(
      QString(
          "SELECT sum(subTotal) AS Total FROM ( "
          "select products.name, quantity , order_id, order_detail.price, "
          "sum(quantity * "
          "order_detail.price)  AS subTotal from order_detail JOIN orders ON "
          "order_detail.fk_order_id=orders.order_id JOIN products ON "
          "order_detail.fk_product_sku=products.sku "
          "where order_id = %1 "
          "GROUP BY(name,quantity,orders.order_id, order_detail.price) ) sub "
          " GROUP BY ROLLUP(sub.subTotal)")
          .arg(orderID));
  model->setQuery(query);

  query.next();
  qDebug() << "Total: " << query.record().value(0).toDouble();

  //  query.clear();

  query.clear();
  query.prepare(
      QString(
          "select sku, quantity , order_id, order_detail.price, sum(quantity * "
          " order_detail.price) AS subTotal from order_detail JOIN "
          "orders ON "
          "order_detail.fk_order_id=orders.order_id JOIN products "
          "ON order_detail.fk_product_sku=products.sku where order_id = %1 "
          "GROUP BY "
          "sku,quantity,orders.order_id, order_detail.price ")
          .arg(orderID));
  model->setQuery(query);
  query.next();

  qDebug() << "Output: " << query.record().value("quantity").toDouble();

  model->setHeaders({"Sku", "Quantity", "orderId", "price", "subTotal"});
  ui->orderViewerTable->setModel(model);
}

/*
select sku, quantity , order_id, order_detail.price,   sum(quantity *
order_detail.price)  AS subTotal  from order_detail JOIN orders ON
order_detail.fk_order_id=orders.order_id JOIN products ON
order_detail.fk_product_sku=products.sku where order_id = 1 GROUP BY
sku,quantity,orders.order_id, order_detail.price

*/

/*

SELECT subTotal, sum(subTotal) AS Total FROM (
select products.name, quantity , order_id, order_detail.price,   sum(quantity *
order_detail.price)  AS subTotal from order_detail JOIN orders ON
order_detail.fk_order_id=orders.order_id JOIN products ON
order_detail.fk_product_sku=products.sku where order_id = 1 GROUP
BY(name,quantity,orders.order_id, order_detail.price) ) sub GROUP BY
ROLLUP(sub.subTotal)

*/

/*
SELECT sum(subTotal) AS Total FROM (
select products.name, quantity , order_id, order_detail.price,   sum(quantity *
order_detail.price)  AS subTotal from order_detail JOIN orders ON
order_detail.fk_order_id=orders.order_id JOIN products ON
order_detail.fk_product_sku=products.sku where order_id = 1 GROUP
BY(name,quantity,orders.order_id, order_detail.price) ) sub GROUP BY
ROLLUP(sub.subTotal) LIMIT 1


*/

void OrderViewer::on_okButton_accepted() {
  accept();
  return;
}
