#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <addressview.h>
#include <ordersview.h>
#include <usersview.h>
#include "dbmanager.h"

class ProductsView;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DbManager *dbM, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_actionAdd_Products_triggered();

    void on_actionAdd_Users_triggered();

    void on_actionAdd_Address_triggered();

private:
    Ui::MainWindow *ui;
    DbManager *_dbM;
    ProductsView *productsView = nullptr;
    UsersView *usersView = nullptr;
    OrdersView *ordersView = nullptr;
    AddressView *addressView = nullptr;
    void releaseMemory(QObject* obj) {if(obj != nullptr) delete obj;}
    void populateTab(QWidget* widget, QMdiArea *mdiArea);
};

#endif // MAINWINDOW_H
