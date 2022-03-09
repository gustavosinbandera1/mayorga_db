#ifndef DIALOG_H
#define DIALOG_H
//#include <userDataObject.h>
#include <QDialog>

#include "dbmanager.h"
#include "userdto.h"

class UserData {
 public:
  static QString userName;  // email
  static QString userEmail;
  static int userId;
  static bool isAdmin;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Login : public QDialog {
  Q_OBJECT

 public:
  /**
   * @brief Login
   * @param dbM database object
   * @param parent
   */
  Login(DbManager *dbM, QWidget *parent = nullptr);
  ~Login();
  /**
   * @brief getCurrentUser refer to the current logged user
   * @return
   */
  QString getCurrentUser() { return currentUser.getEmail(); }

 private slots:
  /**
   * @brief on_buttonBox_accepted this slot is executed when accept button
   * pressed
   */
  void on_buttonBox_accepted();
  /**
   * @brief on_buttonBox_rejected this slot close the whole app
   */
  void on_buttonBox_rejected();

 private:
  Ui::Dialog *ui;
  DbManager *_dbM;
  UserDataObject currentUser;
};
#endif  // DIALOG_H
