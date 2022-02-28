#ifndef REGISTERADMINDIALOG_H
#define REGISTERADMINDIALOG_H

#include <QDialog>

#include "userDTO.h"
namespace Ui {
class RegisterAdminDTO;
}

class QCheckBox;
class RegisterUserDTO : public QDialog {
  Q_OBJECT

 public:
  explicit RegisterUserDTO(QWidget *parent = nullptr);
  ~RegisterUserDTO();
  User getAdmin() const { return _user; }
  QCheckBox *getAdminCheckBox() const;

 private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

 private:
  Ui::RegisterAdminDTO *ui;
  User _user;
};

#endif  // REGISTERADMINDIALOG_H
