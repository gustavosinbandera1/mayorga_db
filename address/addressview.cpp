#include "addressview.h"

#include "addressmodel.h"
#include "ui_addressview.h"

AddressView::AddressView(DbManager* mdb, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddressView) {
  ui->setupUi(this);

  aModel = new AddressModel(mdb, this);
  aRModel = new AddressModel(mdb,this);
  ui->addressTableView->setModel(aRModel->getRelationalModel());
  //ui->addressTableView->setModel(aModel->getModel());

  ui->addressTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->addressTableView->setVisible(true);
  ui->addressTableView->setColumnHidden(3, true);
  ui->addressTableView->setColumnHidden(4, true);
  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->addressTableView->reset();

  ui->addressIDLineEdit->setDisabled(true);
}
//---------------------
AddressView::~AddressView() {
  qDebug() << "Destroying AddressView";
  delete ui;
}

void AddressView::updateAddressModel() {
  ui->addressTableView->setModel(aModel->updateModel());
  aModel->setHeaders();
  ui->addressTableView->setColumnHidden(3, true);
}

void AddressView::updateAddressRModel() {
  ui->addressTableView->setModel(aRModel->updateRModel());
  //aRModel->setHeaders();
  //ui->addressTableView->setColumnHidden(3, true);
}

void AddressView::on_addressTableView_clicked(const QModelIndex& index) {
  qDebug() << "Cell clicked ";
  QSqlTableModel* tmpModel = aModel->getModel();
  QSqlRelationalTableModel *tmpRModel = aRModel->getRelationalModel();
  //    ui->addressLineEdit->setText(tmpModel->index(index.row(),0).data().toString());
  //    ui->cityLineEdit->setText(tmpModel->index(index.row(),1).data().toString());
  //    ui->stateLineEdit->setText(tmpModel->index(index.row(),2).data().toString());

  ui->addressIDLineEdit->setText(
      tmpModel->record(index.row()).value("address_id").toString());
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
  qDebug() << "on_streetNumberTextEdit_copyAvailable "<< b;
}

void AddressView::on_streetNumberTextEdit_undoAvailable(bool b) {
  qDebug() << "on_streetNumberTextEdit_undoAvailable --> "<< b;
}
