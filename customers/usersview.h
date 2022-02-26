#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QWidget>
#include "customModel.h"
#include "dbmanager.h"
namespace Ui {
class UsersView;
}

class UsersView : public QWidget {
  Q_OBJECT

 public:
  explicit UsersView(DbManager *dbm, QWidget *parent = nullptr);
  ~UsersView();
  void updateUserModel();
 private slots:
  void on_userTableView_clicked(const QModelIndex &index);

 private:
  Ui::UsersView *ui;
  CustomModel *cModel;
};

#endif  // USERSVIEW_H
