#include "addressview.h"

#include <queryModel.h>

#include <QDialog>
#include <QMessageBox>
#include <QTime>

#include "addressdto.h"
#include "lineeditordelegate.h"
#include "login.h"
#include "ui_addressview.h"

AddressView::AddressView(DbManager* mdb, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddressView) {
  ui->setupUi(this);
  _dbM = mdb;

  addressModel = new QueryModel(mdb, this);
  lineDelegate = new LineEditorDelegate(this);
  sendQuery();

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);

  ui->addressTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->addressTableView->horizontalHeader()->setVisible(true);
  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setModel(addressModel);

  ui->addressIDLineEdit->setReadOnly(true);
  ui->addressTypeLineEdit->setReadOnly(true);
  ui->cityLineEdit->setReadOnly(true);
  ui->stateLineEdit->setReadOnly(true);
  ui->countryLineEdit->setReadOnly(true);

  ui->streetNumberTextEdit->setReadOnly(true);

  ui->addressTableView->setEditTriggers(
      QAbstractItemView::NoEditTriggers);  // edit sisabled
}
//---------------------
AddressView::~AddressView() {
  qDebug() << "Destroying AddressView";
  delete ui;
}
//----------------------------
void AddressView::updateModel() {
  if (addressModel != nullptr) {
    qDebug() << "deleting address model..";
    delete addressModel;
    addressModel = new QueryModel(_dbM, this);
  }
  sendQuery();
}

//----------------------------
void AddressView::on_addressTableView_clicked(const QModelIndex& index) {
  auto reg = addressModel->getModel();
  int row = index.row();

  ui->addressIDLineEdit->setText(
      reg->record(row).value("address_id").toString());
  ui->cityLineEdit->setText(reg->record(row).value("city").toString());
  ui->stateLineEdit->setText(
      addressModel->getModel()->record(row).value("state").toString());

  ui->streetNumberTextEdit->setPlainText(
      addressModel->getModel()->record(row).value("street_number").toString());

  ui->countryLineEdit->setText(
      reg->record(row).value("country_name").toString());
  ui->addressTypeLineEdit->setText(
      addressModel->getModel()->record(row).value("address_type").toString());
  ui->countryIdLineEdit->setText(
      reg->record(row).value("country_id").toString());

  //------///-----
  address.setCity(reg->record(row).value("city").toString());
  address.setState(reg->record(row).value("state").toString());
  address.setStreetNumber(reg->record(row).value("street_number").toString());
  address.setCountry(reg->record(row).value("country_name").toString());
  address.setType(reg->record(row).value("address_type").toString());
  address.setCountryId(reg->record(row).value("country_id").toInt());
  address.setZipCode(reg->record(row).value("zipcode").toString());
}
//----------------------------
void AddressView::on_addressTableView_doubleClicked(const QModelIndex& index) {
  ui->addressTableView->setItemDelegate(lineDelegate);
}

void AddressView::sendQuery() {
  QSqlQuery query;
  query.prepare(
      "SELECT address_id, city, state, street_number, "
      "address_type , country_name, country_id , zipcode "
      "from customer_address "
      "JOIN customer ON customer_address.fk_customer_id=customer.customer_id "
      "JOIN address ON customer_address.fk_address_id=address.address_id "
      "JOIN country ON address.fk_country_id=country.country_id "
      "WHERE customer_address.fk_customer_id=:id");
  query.bindValue(":id", UserData::userId);

  qDebug() << "error output " << query.lastError().text();
  addressModel->submit();
  addressModel->setQuery(query);
  addressModel->setHeaders({"Address id", "City", "State", "Street Number",
                            "address Type", "Country ", "Country id",
                            "Zip code"});
  ui->addressTableView->setModel(addressModel);
  // ui->addressTableView->setColumnHidden(6, true);
  // ui->addressTableView->setColumnHidden(7, true);
}
//----------------------------
void AddressView::on_streetNumberTextEdit_textChanged() {
  qDebug() << "on_streetNumberTextEdit_textChanged ";
}
//----------------------------
void AddressView::on_streetNumberTextEdit_copyAvailable(bool b) {
  qDebug() << "on_streetNumberTextEdit_copyAvailable " << b;
}
//----------------------------
void AddressView::on_streetNumberTextEdit_undoAvailable(bool b) {
  qDebug() << "on_streetNumberTextEdit_undoAvailable --> " << b;
}
//-------------------------------------------
void AddressView::on_updateButton_clicked() {
  AddressDTO* aDTO = new AddressDTO(this);
  aDTO->address.setCountry(ui->countryLineEdit->text());
  aDTO->address.setState(ui->stateLineEdit->text());
  aDTO->address.setCity(ui->cityLineEdit->text());
  aDTO->address.setType(ui->addressTypeLineEdit->text());
  aDTO->address.setStreetNumber(ui->streetNumberTextEdit->toPlainText());
  aDTO->address.setAddressId(ui->addressIDLineEdit->text().toInt());
  aDTO->address.setCountry(ui->countryLineEdit->text());
  aDTO->address.setCountryId(ui->countryIdLineEdit->text().toInt());
  aDTO->address.setZipCode(address.getZipCode());
  aDTO->updateForm();

  if (aDTO->exec() == QDialog::Rejected) return;
  AddressDataObject address = aDTO->address;
  QSqlQuery q(_dbM->db());
  q.exec(QString("UPDATE address SET "
                 "city='%1', state='%2', street_number='%3', fk_country_id=%4, "
                 "address_type='%5'  WHERE address_id=%6")
             .arg(address.getCity())
             .arg(address.getState())
             .arg(address.getStreetNumber())
             .arg(address.getCountryId())
             .arg(address.getType())
             .arg(address.getAddressId()));
  qDebug() << "Error " << q.lastError().text();
  // addressModel->updateModel();
  this->updateModel();
}
//-------------------------------------
void AddressView::on_deleteButton_clicked() {
  if (!ui->addressIDLineEdit->text().isEmpty()) {
    QMessageBox::StandardButton answer;
    answer = QMessageBox::warning(this, tr("Are you sure"),
                                  tr("This operation cannot be undo .\n"
                                     "Do you want to continue?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes) {
      QSqlQuery query;
      qDebug() << "output "
               << query.exec(
                      QString("DELETE FROM customer_address "
                              "WHERE fk_address_id=%1 AND fk_customer_id=%2")
                          .arg(ui->addressIDLineEdit->text().toInt())
                          .arg(UserData::userId));
      qDebug() << "Error: " << query.lastError().text();

      query.clear();
      query.exec(QString("DELETE FROM address "
                         "WHERE address_id=%1")
                     .arg(ui->addressIDLineEdit->text().toInt()));

      addressModel->updateModel();

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

void AddressView::on_addButton_clicked() {
  AddressDTO aDTO(this);
  if (aDTO.exec() == QDialog::Rejected) return;
  AddressDataObject address = aDTO.address;
  QSqlQuery q(_dbM->db());
  q.exec(QString("INSERT INTO address"
                 "(city,state, street_number, fk_country_id, address_type) "
                 "VALUES ('%1','%2','%3',%4,'%5') returning address_id")
             .arg(address.getCity())
             .arg(address.getState())
             .arg(address.getStreetNumber())
             .arg(address.getCountryId())
             .arg(address.getType()));

  int lastInsertedId = q.lastInsertId().toInt();
  qDebug() << "-------------   response " << lastInsertedId;

  q.clear();
  QDateTime dateTime = QDateTime::currentDateTime();
  q.prepare(
      "INSERT INTO customer_address (fk_customer_id, fk_address_id, "
      "created_date_time) VALUES ( :customer_id, :address_id, :dateTime)");
  q.bindValue(":customer_id", UserData::userId);
  q.bindValue(":address_id", lastInsertedId);
  q.bindValue(":dateTime", dateTime);
  q.exec();

  addressModel->updateModel();
}
