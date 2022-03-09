#include "usersview.h"

#include <lineeditordelegate.h>

#include <QMessageBox>

#include "QCheckBox"
#include "ui_usersview.h"
#include "userdto.h"

UsersView::UsersView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::UsersView) {
  ui->setupUi(this);
  _dbM = dbm;
  userModel = new ReadWriteModel(dbm, "customer", false, this);
  lineDelegate = new LineEditorDelegate(this);
  ui->userTableView->setModel(userModel->getModel());
  userModel->setHeaders(
      {"Customer id", "Name", "Email", "Phone", "Password", "role"});

  ui->userTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->userTableView->horizontalHeader()->setVisible(true);
  ui->userTableView->setAlternatingRowColors(true);
  ui->userTableView->setSortingEnabled(true);
  ui->userTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->userTableView->reset();

  // if(!UserData::isAdmin)
  // ui->productsView->setEditTriggers(QAbstractItemView::NoEditTriggers); //
}
//----------------------------//
//----------------------------//
UsersView::~UsersView() {
  qInfo() << "Destroying UserView";
  delete ui;
}
//----------------------------//
//----------------------------//
void UsersView::updateModel() {
  if (userModel != nullptr) {
    delete userModel;
    userModel = new ReadWriteModel(_dbM, "customer", false, this);
  }
  ui->userTableView->setModel(userModel->getModel());
  userModel->setHeaders(
      {"Customer Id", "Name", "Email", "Phone", "Password", "role"});
}
//----------------------------//
//----------------------------//
void UsersView::on_userTableView_doubleClicked(const QModelIndex& index) {
  ui->userTableView->setItemDelegate(lineDelegate);
}
//----------------------------//
//----------------------------//
void UsersView::on_userTableView_clicked(const QModelIndex& index) {
  int col = index.column();
  int row = index.row();
  auto reg = userModel->getModel()->record(row);

  user.setName(reg.value("name").toString());
  user.setEmail(reg.value("email").toString());
  user.setPhone(reg.value("phone").toString());
}
//----------------------------//
//----------------------------//
void UsersView::on_updateButton_clicked() {
  UserDTO* uDTO = new UserDTO(this);

  uDTO->user.setName(this->user.getName());
  uDTO->user.setEmail(this->user.getEmail());
  uDTO->user.setPhone(this->user.getPhone());
  // PASSSWORD HERE ---------->>>>>>
  uDTO->updateForm();

  if (uDTO->exec() == QDialog::Rejected) return;

  UserDataObject _user = uDTO->user;
  QSqlQuery q(_dbM->db());

  qDebug() << "searching .... " << this->user.getEmail();
  q.exec(QString("UPDATE customer SET name='%1', phone='%2', email='%3' WHERE "
                 "email='%4' ")
             .arg(_user.getName())
             .arg(_user.getPhone())
             .arg(_user.getEmail())
             .arg(this->user.getEmail()));

  qDebug() << "Hopefully working " << q.lastError().text();
}
//----------------------------//
//----------------------------//
void UsersView::on_newButton_clicked() {
  UserDTO dto(this);

  if (dto.exec() == QDialog::Rejected) {
    return;
  }
  UserDataObject admin = dto.getUser();
  QSqlQuery q(_dbM->db());
  q.exec(QString("INSERT INTO customer"
                 "(name, phone, email, password, role) VALUES ('%1', '%2', "
                 "'%3', '%4', '%5')")
             .arg(admin.getName())
             .arg(admin.getPhone())
             .arg(admin.getEmail())
             .arg(_dbM->getHash(admin.getPassword())));
}
//----------------------------//
//----------------------------//
void UsersView::on_deleteButton_clicked() {
  if (!user.getEmail().isEmpty()) {
    QMessageBox::StandardButton answer;
    answer = QMessageBox::warning(this, tr("Are you sure"),
                                  tr("This operation cannot be undo .\n"
                                     "Do you want to continue?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes) {
      QSqlQuery query;
      qDebug() << "output "
               << query.exec(QString("DELETE FROM customer "
                                     "WHERE email = '%1' ")
                                 .arg(user.getEmail()));
      qDebug() << "Error: " << query.lastError().text();

      userModel->updateModel();

      if (query.lastError().text().size() > 1) {
        QMessageBox::warning(
            this, tr("Error .."),
            tr("Register cannot be deleted it has some dependencies.\n"
               "Press  to continue?"),
            QMessageBox::Ok);
      }
    }
  }
}
