#include "mainwindow.h"

#include <addressdto.h>
#include <bits/unique_ptr.h>
#include <orderdetailview.h>

#include <QDate>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QUuid>

#include "addressview.h"
#include "browser.h"
#include "login.h"
#include "orderform.h"
#include "ordersview.h"
#include "productsdto.h"
#include "productsview.h"
#include "ui_mainwindow.h"
#include "ui_userdto.h"
#include "userdto.h"
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
  if (UserData::isAdmin) {
    ui->menuDatabase->setEnabled(true);
  } else {
    ui->menuDatabase->setEnabled(true);
  }
  initTabWidget();
  productsView->updateModel();
  qDebug() << "el user name " << UserData::userName;
  ui->userEmaillabel->setText(UserData::userName);

  qDebug() << QUuid::createUuid().toString();
  addressView->updateModel();
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

  ProductDataObject product = pDTO.getDTO();
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
  UserDTO d(this);
  if (d.exec() == QDialog::Rejected) {
    return;
  }
  UserDataObject admin = d.getUser();
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
void MainWindow::populateTab(QWidget *widget, QMdiArea *mdiArea) {
  mdiArea->closeAllSubWindows();
  auto subwindow = mdiArea->addSubWindow(widget);
  subwindow->showMaximized();
}
//---------------------
void MainWindow::initTabWidget() {
  productsView = new ProductsView(_dbM, this);
  ordersView = new OrdersView(_dbM, this);
  orderDetailView = new OrderDetailView(_dbM, this);
  usersView = new UsersView(_dbM, this);
  addressView = new AddressView(_dbM, this);
  orderForm = new OrderForm(_dbM, this);

  populateTab(productsView, ui->ProductMdiArea);
  populateTab(usersView, ui->userMdiArea);
  populateTab(addressView, ui->addressMdiArea);
  populateTab(ordersView, ui->ordersMdiArea);
  populateTab(orderDetailView, ui->orderDetailsMdiArea);
  populateTab(orderForm, ui->orderFormMdiArea);
}
//---------------------
void MainWindow::on_tabWidget_tabBarClicked(int index) {
  TAB_NAME type = static_cast<TAB_NAME>(index);
  switch (type) {
    case TAB_NAME::PRODUCTS:
      qDebug() << "The user is called : " << UserData::userName;
      productsView->updateModel();
      break;
    case TAB_NAME::USERS:
      usersView->updateModel();
      break;
    case TAB_NAME::ORDERS:
      qDebug() << "Tab Orders..";
      ordersView->updateOrderModel();
      orderDetailView->updateOrderDetailModel();
      break;
    case TAB_NAME::ADDRESSES:
      qDebug() << "Tab Addresses..";
      addressView->updateModel();
      break;
    case TAB_NAME::CREATE_ORDERS:
      qDebug() << "Tab Orders Forms ..";
      break;
    default:
      break;
  }
}
