#include "mainwindow.h"

#include <addressdto.h>
#include <bits/unique_ptr.h>
#include <ui_registeradmindialog.h>

#include <QMdiSubWindow>
#include <QMessageBox>

#include "login.h"
#include "orderform.h"
#include "ordersview.h"
#include "productsdto.h"
#include "productsview.h"
#include "registeruserDTO.h"
#include "ui_mainwindow.h"
#include "usersview.h"

enum class TAB_NAME {
  PRODUCTS,
  USERS,
  ORDERS,
  ADDRESSES,
  CREATE_ORDERS,
  NUM_TABS
};

MainWindow::MainWindow(DbManager *dbM, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _dbM(dbM) {
  ui->setupUi(this);
  Login *d = (Login *)parent;
  currentUser = d->getCurrentUser();

  if (d->getType() == Login::ADMIN) {
    ui->menuDatabase->setEnabled(true);
  } else {
    ui->menuDatabase->setEnabled(false);
  }
  initTabWidget();
  productsView->updateProductsModel();
}
//---------------------
MainWindow::~MainWindow() {
  qDebug() << "Calling main UI destructor";
  delete ui;
}
//---------------------
void MainWindow::on_actionQuit_triggered() { qDebug() << "was clicked quit"; }
//---------------------
void MainWindow::on_actionAbout_triggered() {
  QMessageBox::aboutQt(this, "Qt");
}
//---------------------
void MainWindow::on_actionAdd_Products_triggered() {
  ProductsDTO pDTO(this);
  pDTO.setWindowFlags(Qt::Window | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);

  if (pDTO.exec() == QDialog::Rejected) return;

  Product product = pDTO.getDTO();
  QSqlQuery q(_dbM->db());
  bool status = q.exec(
      QString("INSERT INTO products"
              "(name,description, price, weight) VALUES ( '%1', '%2', %3, %4)")
          .arg(product.getName())
          .arg(product.getDescription())
          .arg(product.getPrice().toDouble())
          .arg(product.getWeight().toDouble()));
}
//---------------------
void MainWindow::on_actionAdd_Users_triggered() {
  RegisterUserDTO d(this);
  auto adminCheckBox = d.getAdminCheckBox();
  adminCheckBox->setChecked(false);
  adminCheckBox->setEnabled(true);
  if (d.exec() == QDialog::Rejected) {
    return;
  }
  User admin = d.getAdmin();
  QSqlQuery q(_dbM->db());
  q.exec(
      QString("INSERT INTO customer"
              "(name, phone, email, password) VALUES ('%1', '%2', '%3', '%4')")
          .arg(admin.getName())
          .arg(admin.getPhone())
          .arg(admin.getEmail())
          .arg(_dbM->getHash(admin.getPassword())));
}
//---------------------
void MainWindow::on_actionAdd_Address_triggered() {
  AddressDTO aDTO(this);
  if (aDTO.exec() == QDialog::Rejected) return;
  Address address = aDTO.getDTO();
  QSqlQuery q(_dbM->db());
  q.exec(QString("INSERT INTO address"
                 "(city,state,zipCode,country) VALUES ('%1','%2','%3',%4)")
             .arg(address.getCity())
             .arg(address.getState())
             .arg(address.getZipCode()));
}
//---------------------
void MainWindow::populateTab(QWidget *widget, QMdiArea *mdiArea) {
  mdiArea->closeAllSubWindows();
  auto subwindow = mdiArea->addSubWindow(widget);
  subwindow->showMaximized();
}
//---------------------
void MainWindow::initTabWidget() {
  productsView = new ProductsView(_dbM, this);
  ordersView = new OrdersView(_dbM, this);
  usersView = new UsersView(_dbM, this);
  addressView = new AddressView(_dbM, this);
  orderForm = new OrderForm(_dbM, this);

  populateTab(productsView, ui->ProductMdiArea);
  populateTab(usersView, ui->userMdiArea);
  populateTab(addressView, ui->addressMdiArea);
  populateTab(ordersView, ui->ordersMdiArea);
  populateTab(orderForm, ui->orderFormMdiArea);
}

void MainWindow::on_tabWidget_tabBarClicked(int index) {
  TAB_NAME type = static_cast<TAB_NAME>(index);
  switch (type) {
    case TAB_NAME::PRODUCTS:
      productsView->updateProductsModel();
      break;
    case TAB_NAME::USERS:
      usersView->updateUserModel();
      break;
    case TAB_NAME::ORDERS:
      ordersView->updateOrderModel();
      break;
    case TAB_NAME::ADDRESSES:
      addressView->updateAddressModel();

      break;
    case TAB_NAME::CREATE_ORDERS:

      break;
    default:
      break;
  }
}
