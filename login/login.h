#ifndef DIALOG_H
#define DIALOG_H
//#include <userDataObject.h>
#include "userDTO.h"
#include <QDialog>

#include "dbmanager.h"

class UserData {
public:
static QString userName; //email
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
    enum Type { USERS, ADMIN };
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

  /**
   * @brief getType return auth type
   * @return
   */
  bool getType() { return mType; }


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
  /**
   * @brief on_registerAdminButton_clicked to create new admin users
   */
  void on_registerAdminButton_clicked();

 private:
  Ui::Dialog *ui;
  DbManager *_dbM;
  void isAdmin();
  int mType;
  UserDataObject currentUser;
};
#endif  // DIALOG_H
