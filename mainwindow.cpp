#include "mainwindow.h"

#include <bits/unique_ptr.h>
#include <ui_registeradmindialog.h>

#include <QMdiSubWindow>
#include <QMessageBox>

#include "login.h"
#include "ordersview.h"
#include "productsdto.h"
#include "productsview.h"
#include "registeruserDTO.h"
#include "ui_mainwindow.h"
#include "usersview.h"

MainWindow::MainWindow(DbManager *dbM, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _dbM(dbM) {
  ui->setupUi(this);
  Login *d = (Login *)parent;

  if (d->getType() == Login::ADMIN) {
    ui->menuDatabase->setEnabled(true);
  } else {
    ui->menuDatabase->setEnabled(false);
  }
  on_tabWidget_currentChanged(0);
}

MainWindow::~MainWindow() {
  qDebug() << "Calling main UI destructor";
  delete ui;
}

void MainWindow::on_actionQuit_triggered() { qDebug() << "was clicked quit"; }

void MainWindow::on_actionAbout_triggered() {
  QMessageBox::aboutQt(this, "Qt");
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  if (index == 0) {
    releaseMemory(productsView);
    productsView = new ProductsView(_dbM, this);
    ui->ProductMdiArea->closeAllSubWindows();
    auto subwindow = ui->ProductMdiArea->addSubWindow(productsView);
    subwindow->showMaximized();

  } else if (index == 1) {
    releaseMemory(usersView);
    usersView = new UsersView(_dbM, this);
    ui->userMdiArea->closeAllSubWindows();
    auto subwindow = ui->userMdiArea->addSubWindow(usersView);
    subwindow->showMaximized();
  } else if (index == 2) {
    releaseMemory(ordersView);
    OrdersView *oView = new OrdersView();
    ui->ordersMdiArea->closeAllSubWindows();
    auto subwindow = ui->ordersMdiArea->addSubWindow(oView);
    subwindow->showMaximized();
  } else if(index == 3) {
      releaseMemory(addressView);
      addressView = new AddressView(_dbM,this);
      ui->addressMdiArea->closeAllSubWindows();
      auto subwindow = ui->addressMdiArea->addSubWindow(addressView);
      subwindow->showMaximized();
  }
}

void MainWindow::on_actionAdd_Products_triggered() {
  ProductsDTO pDTO(this);
  pDTO.setWindowFlags(Qt::Window | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  if (pDTO.exec() == QDialog::Rejected) {
    return;
  }

  Product product = pDTO.getProduct();
  QSqlQuery q(_dbM->db());
  q.exec(
      QString("INSERT INTO products"
              "(description, price, weight) VALUES ( '%1', '%2', '%3')")
          .arg(product.getDescription())
          .arg(product.getPrice().toDouble())
          .arg(product.getWeight().toDouble()));
}

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
          .arg(admin.name())
          .arg(admin.phone())
          .arg(admin.email())
          .arg(_dbM->getHash(admin.password())));
}
