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
  address.setUserId(UserData::userId);
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

  QString country;
  int countryId;
  QString zipcode;
  while (query.next()) {
    country = query.record().value("country_name").toString();
    countryId = query.record().value("country_id").toInt();
    zipcode = query.record().value("zipcode").toString();
    qDebug() << "initializing Addreess DTO......... "
             << "Country: " << country << " Id: " << countryId
             << " zipcde: " << zipcode;
    country_items.append(QPair<QString, int>(country, countryId));
    ui->zipcodeComboBox->addItem(zipcode);
    ui->countryLineEdit->setText(country);
  }
}
//---------------------
AddressDTO::~AddressDTO() {
  qDebug() << "Deleting Address DTO";
  delete ui;
}

void AddressDTO::updateForm() {
  ui->cityLineEdit->setText(address.getCity());
  ui->countryLineEdit->setText(address.getCountry());
  ui->stateLineEdit->setText(address.getState());
  ui->billingRadioButton->setChecked(address.getType() == "billing");
  ui->shippingRadioButton->setChecked(address.getType() == "shipping");
  ui->streetTextEdit->setText(address.getStreetNumber());
  ui->zipcodeComboBox->setCurrentText(address.getZipCode());

}
//---------------------
void AddressDTO::on_buttonBox_rejected() {}
//---------------------
void AddressDTO::verify() {
  qDebug() << "Checking DTO here into button " << ui->cityLineEdit->text();
  address.setCity(ui->cityLineEdit->text());
  address.setState(ui->stateLineEdit->text());
  address.setZipCode(
      ui->zipcodeComboBox->itemData(ui->zipcodeComboBox->currentIndex())
          .toString());
  address.setCountry(ui->countryLineEdit->text());
  address.setStreetNumber(ui->streetTextEdit->toPlainText());
  if (ui->billingRadioButton->isChecked()) {
    address.setType(BILLING_ADDRESS);
  } else {
    address.setType(SHIPPING_ADDRESS);
  }

  if (!address.getCity().isEmpty() && !address.getState().isEmpty() &&
      !address.getStreetNumber().isEmpty()) {
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
    qDebug()<<"the index is "<< index;
  ui->countryLineEdit->setText(country_items[index].first);
  address.setCountryId(country_items[index].second);
}
