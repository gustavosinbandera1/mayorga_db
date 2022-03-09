#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>

class AddressView;
class OrdersView;
class UsersView;
class DbManager;
class ProductsView;
class OrderForm;
class OrderDetailView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(DbManager *dbM, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_actionQuit_triggered();

  void on_actionAbout_triggered();

  void on_actionAdd_Products_triggered();

  void on_actionAdd_Users_triggered();

  void on_tabWidget_tabBarClicked(int index);

 private:
  Ui::MainWindow *ui;
  DbManager *_dbM;
  ProductsView *productsView = nullptr;
  UsersView *usersView = nullptr;
  OrdersView *ordersView = nullptr;
  OrderDetailView *orderDetailView = nullptr;
  AddressView *addressView = nullptr;
  OrderForm *orderForm = nullptr;

  void releaseMemory(QObject *obj) {
    if (obj != nullptr) delete obj;
  }
  void populateTab(QWidget *widget, QMdiArea *mdiArea);
  void initTabWidget();
};

#endif  // MAINWINDOW_H
