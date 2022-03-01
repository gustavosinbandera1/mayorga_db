#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QWidget>
#include "readWriteModel.h"
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

  void on_userTableView_doubleClicked(const QModelIndex &index);

private:
  Ui::UsersView *ui;
  ReadWriteModel *userModel;
  LineEditorDelegate *lineDelegate;
};

#endif  // USERSVIEW_H
