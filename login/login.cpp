#include "login.h"

#include <QCheckBox>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtSql>

#include "dbmanager.h"
#include "ui_login.h"
#include "userdto.h"

QString UserData::userName = "";
QString UserData::userEmail = "";
int UserData::userId = -1;
bool UserData::isAdmin;

Login::Login(DbManager* dbM, QWidget* parent)
    : QDialog(parent), ui(new Ui::Dialog), _dbM(dbM) {
  ui->setupUi(this);
  ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
}
//---------------------
Login::~Login() {
  qInfo() << "Destroying Login";
  delete ui;
}
//---------------------
void Login::on_buttonBox_accepted() {
  if (ui->userLineEdit->text().isEmpty() ||
      ui->passwordLineEdit->text().isEmpty())
    return;

  QPair<QString, int> password;
  password = _dbM->getPasswordFromTable("customer", ui->userLineEdit->text());
  UserData::userName = ui->userLineEdit->text();
  UserData::userEmail = ui->userLineEdit->text();
  UserData::isAdmin = false;

  // UserData::isAdmin = TODO get the data from database

  UserData::userId = password.second;

  if (password.first.size()) {
    if (password.first == _dbM->getHash(ui->passwordLineEdit->text())) {
      accept();
      return;
    } else {
      QMessageBox::information(this, "Ok", "Wrong password!!");
      UserData::userName = "";
      UserData::userEmail = "";
      return;
    }
  }
  QMessageBox::information(this, "Fail", "Wrong email!!");
}
//---------------------
void Login::on_buttonBox_rejected() { reject(); }
