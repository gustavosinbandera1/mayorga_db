#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QWidget>

#include "dbmanager.h"
namespace Ui {
class UsersView;
}

class UsersView : public QWidget {
  Q_OBJECT

 public:
  explicit UsersView(DbManager *dbm, QWidget *parent = nullptr);
  ~UsersView();

 private:
  Ui::UsersView *ui;
};

#endif  // USERSVIEW_H
