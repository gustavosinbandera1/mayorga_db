#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QWidget>
#include "readWriteModel.h"
#include "dbmanager.h"
#include "userDTO.h"

class LineEditorDelegate;
namespace Ui {
class UsersView;
}

class UsersView : public QWidget {
  Q_OBJECT

 public:
  explicit UsersView(DbManager *dbm, QWidget *parent = nullptr);
  ~UsersView();
    void updateModel();
 private slots:
  void on_userTableView_clicked(const QModelIndex &index);

  void on_userTableView_doubleClicked(const QModelIndex &index);
  void on_newButton_clicked();
  void on_deleteButton_clicked();
  void on_updateButton_clicked();

private:
  Ui::UsersView *ui;
  DbManager *_dbM;
  ReadWriteModel *userModel;
  LineEditorDelegate *lineDelegate;
  UserDataObject user;

};

#endif  // USERSVIEW_H
