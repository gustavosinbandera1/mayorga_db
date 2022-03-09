#include "productsdto.h"

#include <QDebug>

#include "ui_productsdto.h"

ProductsDTO::ProductsDTO(QWidget *parent)
    : QDialog(parent), ui(new Ui::ProductsDTO) {
  ui->setupUi(this);
}
//---------------------
ProductsDTO::~ProductsDTO() {
  qInfo() << "Releasing ProductsDTO";
  delete ui;
}

void ProductsDTO::updateForm() {
  ui->nameLineEdit->setText(product.getName());
  ui->priceLineEdit->setText(product.getPrice());
  ui->weightLineEdit->setText(product.getWeight());
  ui->descLineEdit->setText(product.getDescription());
}
//---------------------
void ProductsDTO::on_buttonBox_accepted() {
  // send data to database
  product.setName(ui->nameLineEdit->text());
  product.setDescription(ui->descLineEdit->text());
  product.setPrice(ui->priceLineEdit->text());
  product.setWeight(ui->weightLineEdit->text());
  accept();
}
//---------------------
void ProductsDTO::on_buttonBox_rejected() { reject(); }
