#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QWidget>
//#include "customersModel.h"
#include "dbmanager.h"

class CustomerModel;
namespace Ui {
class UsersView;
}

class UsersView : public QWidget {
  Q_OBJECT

 public:
  explicit UsersView(DbManager *dbm, QWidget *parent = nullptr);
  ~UsersView();

private slots:
    void on_userTableView_clicked(const QModelIndex &index);

private:
  Ui::UsersView *ui;
   CustomerModel* cModel;
};

#endif  // USERSVIEW_H
