#include "productsview.h"

#include "productsModel.h"
#include "ui_productsview.h"

ProductsView::ProductsView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::ProductsView) {
  ui->setupUi(this);
  ProductsModel* pModel = new ProductsModel(dbm, this);
  ui->productsView->setModel(pModel->getProductModel());
  ui->productsView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->productsView->horizontalHeader()->setVisible(true);
}

ProductsView::~ProductsView() { delete ui; }
