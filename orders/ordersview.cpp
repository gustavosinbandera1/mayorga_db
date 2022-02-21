#include "ordersview.h"

#include "ui_ordersview.h"

OrdersView::OrdersView(QWidget *parent)
    : QWidget(parent), ui(new Ui::OrdersView) {
  ui->setupUi(this);
}

OrdersView::~OrdersView() { delete ui; }
