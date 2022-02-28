#include "addressview.h"

#include "ui_addressview.h"

/*
select * from customer_address  join address ON customer_address.fk_address_id=address.address_id WHERE fk_customer_id = 1;
*/
AddressView::AddressView(DbManager* mdb, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddressView) {
    ui->setupUi(this);
    bool isRelational = true;
    model = new CustomModel(mdb, "address", isRelational, this);

    ui->addressTableView->setModel(model->getRelationalModel());
    model->setHeaders({"Id", "City", "State","Country", "Address Type" });
    model->setRelation(4,"country","country_id","country_name");

  ui->addressTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->addressTableView->setVisible(true);
  ui->addressTableView->setColumnHidden(3, true);
  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->addressTableView->reset();
  ui->addressIDLineEdit->setDisabled(true);
  ui->addressTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // edit sisabled
}
//---------------------
AddressView::~AddressView() {
  qDebug() << "Destroying AddressView";
  delete ui;
}

void AddressView::updateAddressModel() {
    qDebug()<<"Updating address rmodel";
 ui->addressTableView->setModel(model->updateRModel());
 model->setHeaders({"Id", "City", "State","Country", "Address Type" });
 model->setRelation(4,"country","country_id","country_name");
 ui->addressTableView->setColumnHidden(3, true);
}

void AddressView::on_addressTableView_clicked(const QModelIndex& index) {
  qDebug() << "Cell clicked ";
  //QSqlTableModel* tmpModel = aModel->getModel();
  QSqlRelationalTableModel *tmpRModel = model->getRelationalModel();
  //ui->addressIDLineEdit->setText(tmpRModel->index(index.row(),0).data().toString());
  //    ui->cityLineEdit->setText(tmpModel->index(index.row(),1).data().toString());
  //    ui->stateLineEdit->setText(tmpModel->index(index.row(),2).data().toString());

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
  qDebug() << "on_streetNumberTextEdit_copyAvailable "<< b;
}

void AddressView::on_streetNumberTextEdit_undoAvailable(bool b) {
  qDebug() << "on_streetNumberTextEdit_undoAvailable --> "<< b;
}
