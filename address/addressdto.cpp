#include "addressdto.h"

#include "ui_addressdto.h"

AddressDTO::AddressDTO(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddressDTO) {
  ui->setupUi(this);
}
//---------------------
AddressDTO::~AddressDTO() { delete ui; }
//---------------------
void AddressDTO::on_buttonBox_accepted() {}
//---------------------
void AddressDTO::on_buttonBox_rejected() {}
