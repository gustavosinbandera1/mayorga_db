#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QWidget>
#include "templateModel.h"
#include "dbmanager.h"

class LineEditorDelegate;
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
  CustomModel *userModel;
  LineEditorDelegate *lineDelegate;
};

#endif  // USERSVIEW_H
