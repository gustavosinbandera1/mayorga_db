#include "addressview.h"

#include <queryModel.h>

#include "ui_addressview.h"

AddressView::AddressView(DbManager* mdb, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddressView) {
  ui->setupUi(this);
  addressModel = new QueryModel(mdb, this);
  QSqlQuery query;
  query.prepare("SELECT * from address ");
  addressModel->setQuery(query);
  addressModel->setHeaders({"1", "2", "3", "4", "5"});
  ui->addressTableView->setModel(addressModel);

  ui->addressTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->addressTableView->setVisible(true);
  ui->addressTableView->setColumnHidden(3, true);
  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->addressTableView->reset();
  ui->addressIDLineEdit->setDisabled(true);
  ui->addressTableView->setEditTriggers(
      QAbstractItemView::NoEditTriggers);  // edit sisabled
}
//---------------------
AddressView::~AddressView() {
  qDebug() << "Destroying AddressView";
  delete ui;
}

void AddressView::updateAddressModel() { addressModel->updateModel(); }

void AddressView::on_addressTableView_clicked(const QModelIndex& index) {
  // QSqlTableModel* tmpRModel = model->getModel();
  QSqlRelationalTableModel* tmpRModel = model->getRelationalModel();

  ui->addressIDLineEdit->setText(
      tmpRModel->record(index.row()).value("address_id").toString());
  ui->cityLineEdit->setText(
      tmpRModel->record(index.row()).value("city").toString());
  ui->stateLineEdit->setText(
      tmpRModel->record(index.row()).value("state").toString());

  ui->streetNumberTextEdit->setPlainText(
      tmpRModel->record(index.row()).value("street_number").toString());

  ui->countryLineEdit->setText(
      tmpRModel->record(index.row()).value("country_name").toString());
  ui->addressTypeLineEdit->setText(
      tmpRModel->record(index.row()).value("address_type").toString());
}

void AddressView::on_streetNumberTextEdit_textChanged() {
  qDebug() << "on_streetNumberTextEdit_textChanged ";
}

void AddressView::on_streetNumberTextEdit_copyAvailable(bool b) {
  qDebug() << "on_streetNumberTextEdit_copyAvailable " << b;
}

void AddressView::on_streetNumberTextEdit_undoAvailable(bool b) {
  qDebug() << "on_streetNumberTextEdit_undoAvailable --> " << b;
}
