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
int UserData::user_id = 0;

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
    UserData::userName ="n@gmail.com";
    UserData::user_id = 1;

    accept();
    return;

    QString password;
    if(ui->customerRadioButton->isChecked()) {
        password = _dbM->getPasswordFromTable("customer",ui->userLineEdit->text());
        mType = Login::USERS;
    } else {
        mType = Login::ADMIN;
        password = _dbM->getPasswordFromTable("administrator", ui->userLineEdit->text());
    }

    currentUser.setEmail(ui->userLineEdit->text());
    UserData::userName = currentUser.getEmail();

    if(password.size()){
        if(password == _dbM->getHash(ui->passwordLineEdit->text())) {
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
