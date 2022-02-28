#include "usersview.h"
#include "ui_usersview.h"

UsersView::UsersView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::UsersView) {
  ui->setupUi(this);
  bool isRelational = false;
  cModel = new CustomModel(dbm, "customer",isRelational, this);

  ui->userTableView->setModel(cModel->getRelationalModel());
  cModel->setHeaders({"Customer id", "Name","Email", "Phone","Password"});
  //cModel->setRelation(4,"address","address_id","city");

  ui->userTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->userTableView->horizontalHeader()->setVisible(true);
  ui->userTableView->setAlternatingRowColors(true);
  ui->userTableView->setSortingEnabled(true);
  ui->userTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->userTableView->reset();
}
//---------------------
UsersView::~UsersView() {
  qInfo() << "Destroying UserView";
  delete ui;
}
//---------------------
void UsersView::updateUserModel() {
    qDebug()<<"Updating User R model";
 ui->userTableView->setModel(cModel->updateModel());
cModel->setHeaders({"Customer_id", "Name","Email", "Phone","Password"});
  //cModel->setRelation(4,"address","address_id","city");
}
//---------------------
void UsersView::on_userTableView_clicked(const QModelIndex& index) {
  for (int i = 0; i < cModel->columnCount(); i++) {
    qInfo() << "data " << cModel->index(index.row(), i).data();
  }
}
