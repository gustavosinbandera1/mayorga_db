#include "addressdto.h"
#include "login.h"
#include "ui_addressdto.h"

AddressDTO::AddressDTO(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddressDTO) {
  ui->setupUi(this);
  ui->userLineEdit->setText(UserData::userName);
  _address.setUserId(UserData::user_id);
  ui->userLineEdit->setReadOnly(true);
}
//---------------------
AddressDTO::~AddressDTO() { delete ui; }
//---------------------
void AddressDTO::on_buttonBox_accepted() {
    // send data to database
    _address.setState(ui->cityLineEdit->text());
    _address.setState(ui->stateLineEdit->text());
    _address.setZipCode(ui->zipcodeComboBox->itemData(ui->zipcodeComboBox->currentIndex()).toString());
    _address.setCountry(ui->countryLineEdit->text());


    accept();
}
//---------------------
void AddressDTO::on_buttonBox_rejected() {

}
