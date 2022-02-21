#include "login.h"
#include "ui_dialog.h"
#include "registeruserDTO.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include "dbmanager.h"
#include <QtSql>
#include <QCheckBox>

Login::Login(DbManager* dbM, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog),
      _dbM(dbM){
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->customerRadioButton->setChecked(true);
}


Login::~Login() {
    delete ui;
}


void Login::on_buttonBox_accepted() {
    bool is_user = false;
    mType = Login::ADMIN;
    accept();
    return;

    QString password;
    if(ui->customerRadioButton->isChecked()) {
        password = _dbM->selectFromTable("customer",ui->userLineEdit->text());
        is_user = true;
        mType = Login::USERS;

    } else {
        is_user = false;
        mType = Login::ADMIN;
        password = _dbM->selectFromTable("administrator", ui->userLineEdit->text());
    }
    if(password.size()){
        if(password == _dbM->getHash(ui->passwordLineEdit->text())) {
            accept();
            return ;
        } else {
            QMessageBox::information(this, "Ok", "Wrong password!!");
            return;
        }

    }
    QMessageBox::information(this, "Fail", "Wrong email!!");
}

void Login::on_buttonBox_rejected() {
    reject();
}

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
           .arg(admin.name())
           .arg(admin.phone())
           .arg(admin.email())
           .arg(_dbM->getHash(admin.password()))
           );
}
