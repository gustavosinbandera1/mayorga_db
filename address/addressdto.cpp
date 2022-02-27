#include "addressdto.h"

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
    qDebug()<< "salida......... "<< countryId;
    countryItems.append(country);
    _country_items.append(QPair<QString,int>(country,countryId));
    ui->zipcodeComboBox->addItem(query.value("zipcode").toString());
    ui->countryLineEdit->setText(country);
  }
}
//---------------------
AddressDTO::~AddressDTO() { delete ui; }
//---------------------
void AddressDTO::on_buttonBox_accepted() {
  // send data to database
    qDebug()<< "Checking DTO here into button "<< ui->cityLineEdit->text();
  _address.setCity(ui->cityLineEdit->text());
  _address.setState(ui->stateLineEdit->text());
  _address.setZipCode(
      ui->zipcodeComboBox->itemData(ui->zipcodeComboBox->currentIndex())
          .toString());
  _address.setCountry(ui->countryLineEdit->text());
  _address.setStreetNumber(ui->streetTextEdit->toPlainText());
    if(ui->billingRadioButton->isChecked()) {
        _address.setType(BILLING_ADDRESS);
    }else {
        _address.setType(SHIPPING_ADDRESS);
    }
  accept();
}
//---------------------
void AddressDTO::on_buttonBox_rejected() {}

void AddressDTO::on_zipcodeComboBox_currentIndexChanged(const QString &arg1) {
  qDebug() << "index has changed " << arg1.toInt();
}

void AddressDTO::on_zipcodeComboBox_currentIndexChanged(int index) {
  qDebug() << "here output country " << countryItems[index];
  ui->countryLineEdit->setText(countryItems[index]);
  ui->countryLineEdit->setText(_country_items[index].first);
  _address.setCountryId(_country_items[index].second);

}

//void AddressDTO::on_textEdit_copyAvailable(bool b)
//{
//    qDebug()<<"111111111111  copy available " << b;
//}

//void AddressDTO::on_textEdit_redoAvailable(bool b)
//{
//        qDebug()<<"222222222  re-do available " << b;
//}

//void AddressDTO::on_textEdit_textChanged()
//{
//    qDebug()<<"3333333333333  text changed ";
//}
