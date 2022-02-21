#include "usersview.h"

#include "customersModel.h"
#include "ui_usersview.h"

UsersView::UsersView(DbManager* dbm, QWidget* parent)
    : QWidget(parent), ui(new Ui::UsersView) {
  ui->setupUi(this);
  CustomerModel* cModel = new CustomerModel(dbm, this);
  ui->userTableView->setModel(cModel->getCustomerModel());
  ui->userTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  ui->userTableView->horizontalHeader()->setVisible(true);
}

UsersView::~UsersView() { delete ui; }
