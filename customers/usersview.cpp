#include "usersview.h"
#include "customersModel.h"
#include "ui_usersview.h"

UsersView::UsersView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::UsersView) {
  ui->setupUi(this);
  cModel = new CustomerModel(dbm, this);
  ui->userTableView->setModel(cModel->getCustomerModel());
  ui->userTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->userTableView->horizontalHeader()->setVisible(true);
  ui->userTableView->setAlternatingRowColors(true);
}
//---------------------
UsersView::~UsersView() {
  qInfo() << "Destroying UserView";
  delete ui;
}
//---------------------
void UsersView::updateUserModel() {
  ui->userTableView->setModel(cModel->updateModel());
}
//---------------------
void UsersView::on_userTableView_clicked(const QModelIndex& index) {
  for (int i = 0; i < cModel->columnCount(); i++) {
    qInfo() << "data " << cModel->index(index.row(), i).data();
  }
}
