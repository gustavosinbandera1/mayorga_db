#ifndef ADDRESSDTO_H
#define ADDRESSDTO_H

#include <QDialog>

/**
 * @brief The Address class
 * DTO class for receiving fata from UI form  AddressDTO
 */

class AddressDataObject {
 public:
  AddressDataObject(){};

  int getUserId() { return user_id; }
  void setUserId(int id) { user_id = id; }

  QString getCity() const { return city; }
  void setCity(const QString &value) { city = value; }

  QString getState() const { return state; }
  void setState(const QString &value) { state = value; }

  QString getZipCode() const { return zipCode; }
  void setZipCode(const QString &value) { zipCode = value; }

  QString getCountry() const { return country; }
  void setCountry(const QString &value) { country = value; }

  QString getStreetNumber() const { return streetNumber; }
  void setStreetNumber(const QString &value) { streetNumber = value; }

  QString getType() const { return type; }
  void setType(const QString &value) { type = value; }

  int getCountryId() const { return country_id; }
  void setCountryId(const int &value) { country_id = value; }

  int getAddressId() const { return address_id; }
  void setAddressId(const int &value) { address_id = value; }

 private:
  int user_id;
  QString city;
  QString state;
  QString zipCode;
  QString country;
  QString streetNumber;
  QString type;
  int address_id;
  int country_id;
};

/**
 * Form for capturing user information about addressess
 */

namespace Ui {
class AddressDTO;
}

class AddressDTO : public QDialog {
  Q_OBJECT

 public:
  explicit AddressDTO(QWidget *parent = nullptr);
 ~AddressDTO();

  void updateForm();
  AddressDataObject address;
  QList<QPair<QString, int>> country_items;

 private slots:
  void on_buttonBox_rejected();
  void on_zipcodeComboBox_currentIndexChanged(const QString &arg1);
  void on_zipcodeComboBox_currentIndexChanged(int index);
  //    void on_textEdit_copyAvailable(bool b);
  //    void on_textEdit_redoAvailable(bool b);
  //    void on_textEdit_textChanged();

 private:
  Ui::AddressDTO *ui;
  void verify();
};

#endif  // ADDRESSDTO_H
