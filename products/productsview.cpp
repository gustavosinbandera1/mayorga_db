#include "productsview.h"

#include <typeinfo>
#include "productsModel.h"
#include "ui_productsview.h"
#include "lineeditordelegate.h"

ProductsView::ProductsView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::ProductsView) {
  ui->setupUi(this);
  pModel = new ProductsModel(dbm, this);
  SpinBoxDelegate = new SpinboxDelegate(this);
  lineDelegate = new LineEditorDelegate(this);
  ui->productsView->setModel(pModel->getProductModel());
  ui->productsView->setSortingEnabled(true);
  ui->productsView->sortByColumn(0, Qt::AscendingOrder);
  ui->productsView->reset();

  ui->productsView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->productsView->horizontalHeader()->setVisible(true);
  ui->productsView->setAlternatingRowColors(true);
}
//---------------------
ProductsView::~ProductsView() {
  qInfo() << "Destroying ProductsView";
  delete ui;
}
//---------------------
void ProductsView::updateProductsModel() {
  ui->productsView->setModel(pModel->upadateModel());
}
//---------------------
void ProductsView::on_productsView_doubleClicked(const QModelIndex &index) {
  qDebug() << "Doble click on item " << index.row() << " , " << index.column()
           << " = " << index.data();

  if(isInteger(index.data())){
       qDebug() << "It is an number ";
       ui->productsView->setItemDelegate(SpinBoxDelegate);
       //set item delegate to number
  }else if(isString(index.data())){
       qDebug() << "it is a string ";
       ui->productsView->setItemDelegate(lineDelegate);
  }
}

bool ProductsView::isInteger(const QVariant &variant) {
  switch (variant.userType()) {
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
    case QMetaType::Double:
      return true;
  }
  return false;
}

bool ProductsView::isString(const QVariant &variant) {
  return variant.userType() == QMetaType::QString;
}
