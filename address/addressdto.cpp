#include "addressdto.h"

#include <QMessageBox>

#include "login.h"
#include "ui_addressdto.h"

#define SHIPPING_ADDRESS "shipping"
#define BILLING_ADDRESS "billing"

AddressDTO::AddressDTO(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddressDTO) {
  ui->setupUi(this);
  ui->userLineEdit->setText(UserData::userName);
  _address.setUserId(UserData::userId);
  ui->userLineEdit->setReadOnly(true);
  ui->countryLineEdit->setReadOnly(true);

  ui->billingRadioButton->setChecked(true);

  connect(ui->buttonBox, &QDialogButtonBox::accepted, this,
          &AddressDTO::verify);

  connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
          [=]() { qDebug("cancel"); });
  connect(ui->buttonBox, &QDialogButtonBox::rejected, this,
          [=]() { reject(); });

  QSqlQuery query;
  QString c = QString("SELECT * FROM %1 ").arg("country");
  if (!query.exec(c)) {
    qDebug() << "--------------------error--------------------------";
  }

  // tmpRModel->record(index.row()).value("street_number").toString());

  countryItems.clear();
  QString country;
  int countryId;
  while (query.next()) {
    country = query.record().value("country_name").toString();
    countryId = query.record().value("country_id").toInt();
    qDebug() << "output......... " << countryId;
    countryItems.append(country);
    _country_items.append(QPair<QString, int>(country, countryId));
    ui->zipcodeComboBox->addItem(query.value("zipcode").toString());
    ui->countryLineEdit->setText(country);
  }
}
//---------------------
AddressDTO::~AddressDTO() { delete ui; }
//---------------------
void AddressDTO::on_buttonBox_rejected() {}
//---------------------
void AddressDTO::verify() {
  qDebug() << "Checking DTO here into button " << ui->cityLineEdit->text();
  _address.setCity(ui->cityLineEdit->text());
  _address.setState(ui->stateLineEdit->text());
  _address.setZipCode(
      ui->zipcodeComboBox->itemData(ui->zipcodeComboBox->currentIndex())
          .toString());
  _address.setCountry(ui->countryLineEdit->text());
  _address.setStreetNumber(ui->streetTextEdit->toPlainText());
  if (ui->billingRadioButton->isChecked()) {
    _address.setType(BILLING_ADDRESS);
  } else {
    _address.setType(SHIPPING_ADDRESS);
  }

  if (!_address.getCity().isEmpty() && !_address.getState().isEmpty() &&
      !_address.getStreetNumber().isEmpty()) {
    accept();
    return;
  }

  QMessageBox::StandardButton answer;
  answer = QMessageBox::warning(
      this, tr("Incomplete Form"),
      tr("The form does not contain all the necessary information.\n"
         "Do you want to discard it?"),
      QMessageBox::Yes | QMessageBox::No);

  if (answer == QMessageBox::Yes) reject();
}
//---------------------
void AddressDTO::on_zipcodeComboBox_currentIndexChanged(const QString &arg1) {
  qDebug() << "index has changed " << arg1.toInt();
}
//---------------------
void AddressDTO::on_zipcodeComboBox_currentIndexChanged(int index) {
  qDebug() << "here output country " << countryItems[index];
  ui->countryLineEdit->setText(countryItems[index]);
  ui->countryLineEdit->setText(_country_items[index].first);
  _address.setCountryId(_country_items[index].second);
}
