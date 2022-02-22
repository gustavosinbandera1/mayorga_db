#include "productsdto.h"
#include <QDebug>
#include "ui_productsdto.h"

ProductsDTO::ProductsDTO(QWidget *parent)
    : QDialog(parent), ui(new Ui::ProductsDTO) {
  ui->setupUi(this);
}

ProductsDTO::~ProductsDTO() {
    qInfo()<<"Releasing ProductsDTO";
    delete ui;

}

void ProductsDTO::on_buttonBox_accepted() {
  // send data to database
  _product.setSku(ui->skuLineEdit->text());
  _product.setDescription(ui->descLineEdit->text());
  _product.setPrice(ui->priceLineEdit->text());
  _product.setWeight(ui->weightLineEdit->text());
  accept();

}

void ProductsDTO::on_buttonBox_rejected() { reject(); }
