#include "usersview.h"

#include <lineeditordelegate.h>

#include "ui_usersview.h"
#include "userDTO.h"

UsersView::UsersView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::UsersView) {
  ui->setupUi(this);
  _dbM = dbm;
  userModel = new ReadWriteModel(dbm, "customer", false, this);
  lineDelegate = new LineEditorDelegate(this);

  ui->userTableView->setModel(userModel);
  userModel->setHeaders({"Customer id", "Name", "Email", "Phone", "Password"});

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
  ui->userTableView->setModel(userModel);
  userModel->setHeaders({"Customer Id", "Name", "Email", "Phone", "Password"});
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
    UserDTO *uDTO = new UserDTO(this);

    uDTO->user.setName(this->user.getName());
    uDTO->user.setEmail(this->user.getEmail());
    uDTO->user.setPhone(this->user.getPhone());
    //PASSSWORD HERE ---------->>>>>>
    uDTO->updateForm();

    if(uDTO->exec() == QDialog::Rejected) return;

    UserDataObject user = uDTO->user;
    QSqlQuery q(_dbM->db());
    qDebug()<<"Going to update "<<"Name: " << user.getName()
           <<" -- "<<"Email: "<< user.getEmail()
          << "Phone: " << user.getPhone();

    q.exec(QString("UPDATE customer SET name='%1',email='%2', "
                   "phone='%3' "
                   "WHERE email='%4'")
               .arg(user.getName())
               .arg(user.getEmail())
               .arg(user.getPhone())
               .arg(user.getEmail())
           );
    qDebug() << "****************** error : >> " << q.lastError().text();

}
//----------------------------//
//----------------------------//
void UsersView::on_newButton_clicked() {}
//-------------------------
void UsersView::on_deleteButton_clicked() {}

