#ifndef REGISTERADMINDIALOG_H
#define REGISTERADMINDIALOG_H

#include <QDialog>

class QCheckBox;

class UserDataObject {
 public:
  UserDataObject(){};
  int id() const { return mId; }
  QString getName() const { return mName; }
  QString getPhone() const { return mPhone; }
  QString getEmail() const { return mEmail; }
  QString getPassword() const { return mPassword; }

  void setId(int id) { mId = id; }
  void setName(const QString& name) { mName = name; }
  void setPhone(const QString& phone) { mPhone = phone; }
  void setEmail(const QString& email) { mEmail = email; }
  void setPassword(const QString& password) { mPassword = password; }

 private:
  int mId;
  QString mName;
  QString mPhone;
  QString mEmail;
  QString mPassword;
};

namespace Ui {
class UserDTO;
}


class UserDTO : public QDialog {
  Q_OBJECT

 public:
  explicit UserDTO(QWidget* parent = nullptr);
  ~UserDTO();
  void updateForm();
  UserDataObject getAdmin() const { return user; }
  QCheckBox* getAdminCheckBox() const;
  UserDataObject user;

 private slots:
  void on_buttonBox_accepted();
  void on_buttonBox_rejected();

 private:
  Ui::UserDTO* ui;
};

#endif  // REGISTERADMINDIALOG_H
