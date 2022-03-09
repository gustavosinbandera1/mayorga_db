#include "userdto.h"

#include <QCheckBox>
#include <QMessageBox>

#include "ui_userdto.h"

UserDTO::UserDTO(QWidget *parent) : QDialog(parent), ui(new Ui::UserDTO) {
  ui->setupUi(this);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
  ui->repeatPasswordLineEdit->setEchoMode(QLineEdit::Password);
}
//----------------------------//
//----------------------------//
UserDTO::~UserDTO() { delete ui; }
//----------------------------//
//----------------------------//
// QCheckBox *UserDTO::getAdminCheckBox() const { return ui->adminCheckBox; }
//----------------------------//
//----------------------------//
void UserDTO::updateForm() {
  ui->emailLineEdit->setText(user.getEmail());
  ui->phoneLineEdit->setText(user.getPhone());
  ui->userLineEdit->setText(user.getName());
  // PASSWORD HERE TO BE ADDED !!!!!
}
//----------------------------//
//----------------------------//
void UserDTO::on_buttonBox_accepted() {
  user.setId(1);
  user.setPhone(ui->phoneLineEdit->text());
  user.setEmail(ui->emailLineEdit->text());
  user.setName(ui->userLineEdit->text());
  user.setPassword(ui->passwordLineEdit->text());
  // user.setRole(ui->roleLineEdit->text());

  if (user.getPassword() != ui->repeatPasswordLineEdit->text()) {
    QMessageBox::critical(this, "Error", "passowrd mismatch");
    return;
  }
  accept();
}
//----------------------------//
//----------------------------//
void UserDTO::on_buttonBox_rejected() { reject(); }
