#include "productsview.h"
#include "login.h"
#include <readWriteModel.h>
#include <typeinfo>
#include "ui_productsview.h"
#include "lineeditordelegate.h"

ProductsView::ProductsView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::ProductsView) {
  ui->setupUi(this);

  _productModel = new ReadWriteModel(dbm,"products",false, this);


  ui->productsView->setModel(_productModel);
  _productModel->setHeaders({"sku","name","description","price","weight"});

  SpinBoxDelegate = new SpinboxDelegate(this);
  lineDelegate = new LineEditorDelegate(this);

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
void ProductsView::updateModel() {
    ui->productsView->setModel(_productModel->updateModel());
    _productModel->setHeaders({"sku","name","description","price","weight"});
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
//----------------------------
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
//----------------------------
bool ProductsView::isString(const QVariant &variant) {
  return variant.userType() == QMetaType::QString;
}

