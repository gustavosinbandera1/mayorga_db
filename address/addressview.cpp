#include "addressview.h"

#include <queryModel.h>

#include <QDialog>
#include <QMessageBox>

#include "addressdto.h"
#include "lineeditordelegate.h"
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

  ui->addressIDLineEdit->setReadOnly(true);
  ui->addressTypeLineEdit->setReadOnly(true);
  ui->cityLineEdit->setReadOnly(true);
  ui->stateLineEdit->setReadOnly(true);
  ui->countryLineEdit->setReadOnly(true);

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
    delete addressModel;
    addressModel = new QueryModel(_dbM, this);
  }
  sendQuery();
}

//----------------------------
void AddressView::on_addressTableView_clicked(const QModelIndex& index) {
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
//----------------------------
void AddressView::on_addressTableView_doubleClicked(const QModelIndex& index) {
  ui->addressTableView->setItemDelegate(lineDelegate);
}

void AddressView::sendQuery() {
  QSqlQuery query;
  query.prepare(
      "SELECT address_id, city, state, street_number, "
      "address_type, country_name from address "
      "JOIN country ON address.fk_country_id=country.country_id");
  addressModel->submit();
  addressModel->setQuery(query);
  addressModel->setHeaders({"address_id", "city", "State", "Street Number",
                            "address Type", "country "});
  ui->addressTableView->setModel(addressModel);
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
               << query.exec(QString("DELETE FROM address "
                                     "WHERE address_id=%1")
                                 .arg(ui->addressIDLineEdit->text().toInt()));
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

void AddressView::on_updateButton_clicked() {
  AddressDTO* aDTO = new AddressDTO(this);
  qDebug()<<"SALIDA!!! "<< ui->stateLineEdit->text()<<" -- "<<ui->cityLineEdit->text();
  aDTO->address.setCountry(ui->countryLineEdit->text());
  //aDTO->getDTO().setZipCode(ui->);
  aDTO->address.setState(ui->stateLineEdit->text());
  aDTO->address.setCity(ui->cityLineEdit->text());
  aDTO->address.setType(ui->addressTypeLineEdit->text());
  aDTO->address.setStreetNumber(ui->streetNumberTextEdit->toPlainText());
  aDTO->updateForm();
  aDTO->show();

}
