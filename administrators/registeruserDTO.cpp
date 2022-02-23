#include "registeruserDTO.h"

#include <QCheckBox>
#include <QMessageBox>

#include "ui_registeradmindialog.h"

RegisterUserDTO::RegisterUserDTO(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegisterAdminDTO), _user(-1, "", "", "", "") {
  ui->setupUi(this);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  ui->repeatPasswordLineEdit->setEchoMode(QLineEdit::Password);
}
//---------------------
RegisterUserDTO::~RegisterUserDTO() { delete ui; }
//---------------------
QCheckBox *RegisterUserDTO::getAdminCheckBox() const {
  return ui->adminCheckBox;
}
//---------------------
void RegisterUserDTO::on_buttonBox_accepted() {
  _user.setId(1);
  _user.setPhone(ui->phoneLineEdit->text());
  _user.setEmail(ui->emailLineEdit->text());
  _user.setName(ui->userLineEdit->text());
  _user.setPassword(ui->passwordLineEdit->text());
  if (_user.password() != ui->repeatPasswordLineEdit->text()) {
    QMessageBox::critical(this, "Error", "passowrd mismatch");
    return;
  }
  accept();
}
//---------------------
void RegisterUserDTO::on_buttonBox_rejected() { reject(); }
