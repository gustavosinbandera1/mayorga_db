#include "login.h"
#include "ui_login.h"
#include "registeruserDTO.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "dbmanager.h"
#include <QtSql>
#include <QCheckBox>


QString UserData::userName = "";
QString UserData::userEmail = "";
int UserData::userId = -1;
bool UserData::isAdmin;


Login::Login(DbManager* dbM, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog),
      _dbM(dbM){
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->customerRadioButton->setChecked(true);
}
//---------------------
Login::~Login() {
    qInfo()<<"Destroying Login";
    delete ui;
}
//---------------------
void Login::on_buttonBox_accepted() {
//    if(ui->userLineEdit->text().isEmpty() || ui->passwordLineEdit->text().isEmpty())
//        return;

    mType = Login::ADMIN;
    UserData::userEmail ="n@gmail.com";
    UserData::userName ="gustavo";
    UserData::userId = 1;
    UserData::isAdmin = true;

    accept();
    return;

    // QPair<"password", userId>
    QPair<QString, int>  password;   // pasword and user id
    if(ui->customerRadioButton->isChecked()) {
        password = _dbM->getPasswordFromTable("customer",ui->userLineEdit->text());
        mType = Login::USERS;
        UserData::isAdmin = false;
        UserData::userId = password.second;

    } else {
        mType = Login::ADMIN;
        UserData::isAdmin = true;
        password = _dbM->getPasswordFromTable("administrator", ui->userLineEdit->text());
    }

    //currentUser.setEmail(ui->userLineEdit->text());
    UserData::userName = ui->userLineEdit->text();
     UserData::userEmail =ui->userLineEdit->text();
    UserData::isAdmin = bool(mType);
    UserData::userId = password.second;

    if(password.first.size()){
        if(password.first == _dbM->getHash(ui->passwordLineEdit->text())) {
            accept();
            return ;
        } else {
            QMessageBox::information(this, "Ok", "Wrong password!!");
            UserData::userName = "";
            return;
        }

    }
    QMessageBox::information(this, "Fail", "Wrong email!!");
}
//---------------------
void Login::on_buttonBox_rejected() {
    reject();
}
//---------------------
void Login::on_registerAdminButton_clicked() {
    RegisterUserDTO d(this);
    auto adminCheckBox = d.getAdminCheckBox();
    adminCheckBox->setChecked(true);
    adminCheckBox->setEnabled(false);
    if(d.exec() == QDialog::Rejected) {
        return;
    }
    User admin = d.getAdmin();
    QSqlQuery q(_dbM->db());
    q.exec(QString("INSERT INTO administrator"
                   "(name, phone, email, password) VALUES ('%1', '%2', '%3', '%4')")
           .arg(admin.getName())
           .arg(admin.getPhone())
           .arg(admin.getEmail())
           .arg(_dbM->getHash(admin.getPassword()))
           );
}
