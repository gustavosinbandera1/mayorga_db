#include "addressview.h"

#include <queryModel.h>

#include "lineeditordelegate.h"
#include "ui_addressview.h"

AddressView::AddressView(DbManager* mdb, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddressView) {
  ui->setupUi(this);

  addressModel = new QueryModel(mdb, this);

  QSqlQuery query;
  query.prepare(
      "SELECT address_id, city, state, street_number, "
      "address_type, country_name from address "
      "JOIN country ON address.fk_country_id=country.country_id");

  addressModel->setQuery(query);
  ui->addressTableView->setModel(addressModel);
  addressModel->setHeaders({"address_id", "city", "State", "Street Number",
                            "address Type", "country Id"});

  lineDelegate = new LineEditorDelegate(this);

  ui->addressTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->addressTableView->setVisible(true);
  // ui->addressTableView->setColumnHidden(3, true);

  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);
  // ui->addressTableView->reset();
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
  qDebug() << "Item CLicked!!!!..";
  ui->addressIDLineEdit->setText(addressModel->getModel()
                                     ->record(index.row())
                                     .value("address_id")
                                     .toString());
  ui->cityLineEdit->setText(
      addressModel->getModel()->record(index.row()).value("city").toString());
  ui->stateLineEdit->setText(
      addressModel->getModel()->record(index.row()).value("state").toString());

  ui->streetNumberTextEdit->setPlainText(addressModel->getModel()
                                             ->record(index.row())
                                             .value("street_number")
                                             .toString());

  ui->countryLineEdit->setText(addressModel->getModel()
                                   ->record(index.row())
                                   .value("country_name")
                                   .toString());
  ui->addressTypeLineEdit->setText(addressModel->getModel()
                                       ->record(index.row())
                                       .value("address_type")
                                       .toString());
}

void AddressView::on_addressTableView_doubleClicked(const QModelIndex& index) {
  ui->addressTableView->setItemDelegate(lineDelegate);
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
