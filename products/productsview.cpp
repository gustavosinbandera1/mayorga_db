#include "productsview.h"
#include "login.h"
#include <typeinfo>
#include "ui_productsview.h"
#include "lineeditordelegate.h"

ProductsView::ProductsView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::ProductsView) {
  ui->setupUi(this);
  bool isRelational = false;
  pModel = new CustomModel(dbm, "products",isRelational ,this);

  // Delegators
  SpinBoxDelegate = new SpinboxDelegate(this);
  lineDelegate = new LineEditorDelegate(this);
  //comboBoxDelegate = new ComboBoxDelegate(dbm, "products", "name", this);

  ui->productsView->setModel(pModel->getModel());
  pModel->setHeaders({"Sku", "Name", "Description","Price", "Weight" });

  ui->productsView->setSortingEnabled(true);
  ui->productsView->sortByColumn(0, Qt::AscendingOrder);
  ui->productsView->reset();

  ui->productsView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->productsView->horizontalHeader()->setVisible(true);
  ui->productsView->setAlternatingRowColors(true);

  //ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers); // edit sisabled

}
//---------------------
ProductsView::~ProductsView() {
  qInfo() << "Destroying ProductsView";
  delete ui;
}
//---------------------
void ProductsView::updateProductsModel() {
  ui->productsView->setModel(pModel->updateModel());
}
//---------------------
void ProductsView::on_productsView_doubleClicked(const QModelIndex &index) {
  qDebug() << "Doble click on item " << index.row() << " , " << index.column()
           << " = " << index.data();

  if(isInteger(index.data())){
       ui->productsView->setItemDelegate(SpinBoxDelegate);
  }else if(isString(index.data())){
       ui->productsView->setItemDelegate(lineDelegate);
       //ui->productsView->setItemDelegate(comboBoxDelegate);
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
