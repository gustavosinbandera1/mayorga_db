#include "productsview.h"

#include "productsModel.h"
#include "ui_productsview.h"

ProductsView::ProductsView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::ProductsView) {
  ui->setupUi(this);
  pModel = new ProductsModel(dbm, this);
  ui->productsView->setModel(pModel->getProductModel());
  ui->productsView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->productsView->horizontalHeader()->setVisible(true);
  ui->productsView->setAlternatingRowColors(true);
}

ProductsView::~ProductsView() {
  qInfo() << "Destroying ProductsView";
  delete ui;
}

void ProductsView::on_productsView_clicked(const QModelIndex& index) {
  for (int i = 0; i < pModel->columnCount(); i++) {
    qInfo() << "data " << pModel->index(index.row(), i).data();
  }
}
