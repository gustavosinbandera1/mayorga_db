#include "usersview.h"

#include <lineeditordelegate.h>

#include "ui_usersview.h"

UsersView::UsersView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::UsersView) {
  ui->setupUi(this);

  bool isRelational = false;

  userModel = new ReadWriteModel(dbm, "customer", isRelational, this);
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
}
//---------------------
UsersView::~UsersView() {
  qInfo() << "Destroying UserView";
  delete ui;
}
//---------------------
void UsersView::updateUserModel() {
  ui->userTableView->setModel(userModel->updateModel());
  userModel->setHeaders({"Customer Id", "Name", "Email", "Phone", "Password"});
}
//---------------------
void UsersView::on_userTableView_clicked(const QModelIndex& index) {
  qDebug() << "---------- " << index.data();
  int col = index.column();
  int row = index.row();
  int columnCount = userModel->columnCount();
  int rowCount = userModel->rowCount();

  qDebug() << "Model "
           << "x: " << rowCount << " y: " << columnCount << " Has changed at "
           << row << "," << col;

  for (int i = 0; i < userModel->columnCount(); i++) {
    qDebug() << "data[ " << index.row() << "] [" << i << "] "
             << userModel->index(index.row(), i).data();
  }
}

void UsersView::on_userTableView_doubleClicked(const QModelIndex& index) {
  ui->userTableView->setItemDelegate(lineDelegate);
}
