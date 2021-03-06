#include "productsview.h"

#include <readWriteModel.h>

#include <QMessageBox>
#include <QStandardItem>
#include <typeinfo>

#include "lineeditordelegate.h"
#include "login.h"
#include "productsdto.h"
#include "ui_productsview.h"

ProductsView::ProductsView(DbManager *dbm, QWidget *parent)
    : QWidget(parent), ui(new Ui::ProductsView) {
  ui->setupUi(this);
  _dbM = dbm;
  productModel = new ReadWriteModel(dbm, "products", false, this);
  SpinBoxDelegate = new SpinboxDelegate(this);
  lineDelegate = new LineEditorDelegate(this);

  ui->productsView->setModel(productModel);
  productModel->setHeaders({"sku", "name", "description", "price", "weight"});

  ui->productsView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->productsView->horizontalHeader()->setVisible(true);
  ui->productsView->setAlternatingRowColors(true);

  ui->productsView->setEnabled(true);
  ui->productsView->sortByColumn(0, Qt::AscendingOrder);
  ui->productsView->setSortingEnabled(true);
  ui->productsView->reset();

  // if(!UserData::isAdmin)
  // ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers); //
}
//----------------------------------------------------//
//----------------------------------------------------//
ProductsView::~ProductsView() {
  qInfo() << "Destroying ProductsView";
  delete ui;
}
//----------------------------------------------------//
//----------------------------------------------------//
void ProductsView::updateModel() {
  ui->productsView->setModel(productModel);
  productModel->setHeaders({"Sku", "Name", "Description", "Price", "Weight"});
}
//----------------------------------------------------//
//----------------------------------------------------//
void ProductsView::on_productsView_doubleClicked(const QModelIndex &index) {
  if (isInteger(index.data())) {
    ui->productsView->setItemDelegate(SpinBoxDelegate);
  } else if (isString(index.data())) {
    ui->productsView->setItemDelegate(lineDelegate);
  }
}
//----------------------------------------------------//
//----------------------------------------------------//
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
//----------------------------------------------------//
//----------------------------------------------------//
bool ProductsView::isString(const QVariant &variant) {
  return variant.userType() == QMetaType::QString;
}
//----------------------------------------------------//
//----------------------------------------------------//
void ProductsView::on_updateButton_clicked() {
  ProductsDTO *pDTO = new ProductsDTO(this);
  pDTO->product.setName(this->product.getName());
  pDTO->product.setSku(this->product.getSku());
  pDTO->product.setDescription(this->product.getDescription());
  pDTO->product.setPrice(this->product.getPrice());
  pDTO->product.setWeight(this->product.getWeight());
  pDTO->updateForm();

  if (pDTO->exec() == QDialog::Rejected) return;

  ProductDataObject product = pDTO->product;
  QSqlQuery q(_dbM->db());

  q.exec(QString("UPDATE products SET name='%1',price=%2, "
                 "description='%3', weight=%4 "
                 "WHERE sku=%5")
             .arg(product.getName())
             .arg(product.getPrice())
             .arg(product.getDescription())
             .arg(product.getWeight())
             .arg(product.getSku()));
  qDebug() << "****************** error : >> " << q.lastError().text();
  productModel->updateModel();
}
//----------------------------------------------------//
//----------------------------------------------------//
void ProductsView::on_deleteButton_clicked() {
  if (!product.getSku().isEmpty()) {
    QMessageBox::StandardButton answer;
    answer = QMessageBox::warning(this, tr("Are you sure"),
                                  tr("This operation cannot be undo .\n"
                                     "Do you want to continue?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes) {
      QSqlQuery query;
      qDebug() << "output "
               << query.exec(QString("DELETE FROM products "
                                     "WHERE sku=%1")
                                 .arg(product.getSku()));
      productModel->updateModel();
      qDebug() << "Error: " << query.lastError().text().size();
      if (query.lastError().text().size() > 1) {
        QMessageBox::warning(
            this, tr("Error .."),
            tr("Register cannot be deleted it has some dependencies.\n"
               "Press  to continue?"),
            QMessageBox::Ok);
      }
    }
  }
}
//----------------------------------------------------//
//----------------------------------------------------//
void ProductsView::on_newButton_clicked() {
  ProductsDTO *pDTO = new ProductsDTO(this);

  if (pDTO->exec() == QDialog::Rejected) return;

  ProductDataObject product = pDTO->product;
  QSqlQuery q(_dbM->db());
  bool status = q.exec(
      QString("INSERT INTO products"
              "(name,description, price, weight) VALUES ( '%1', '%2', %3, %4)")
          .arg(product.getName())
          .arg(product.getDescription())
          .arg(product.getPrice().toDouble())
          .arg(product.getWeight().toDouble()));
  qDebug() << "****************** error : >> " << q.lastError().text();
  productModel->updateModel();
}
//----------------------------------------------------//
//----------------------------------------------------//
void ProductsView::on_productsView_clicked(const QModelIndex &index) {
  int col = index.column();
  int row = index.row();
  auto reg = productModel->getModel()->record(row);

  // product.setSku()
  auto tmp = productModel->data(index).toString();
  qDebug() << "product output ---------" << tmp << " -- ";
  qDebug() << row << "," << col;

  product.setSku(reg.value("sku").toString());
  product.setName(reg.value("name").toString());
  product.setDescription(reg.value("description").toString());
  product.setPrice(reg.value("price").toString());
  product.setWeight(reg.value("weight").toString());
}
