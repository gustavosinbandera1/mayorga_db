#ifndef ADDRESSDTO_H
#define ADDRESSDTO_H

#include <QDialog>


//class QSqlQuery;
class Address {
public:
    Address(int user_id,
            QString city,
            QString state,
            QString zipcode,
            QString country,
            QString streetNumber);

    Address(){};

    int getUserId() {return user_id;}
    void setUserId(int id) {user_id = id;}

    QString getCity() const {return city;}
    void setCity(const QString &value) {city = value;}

    QString getState() const {return state;}
    void setState(const QString &value) {state = value;}

    QString getZipCode() const {return zipCode;}
    void setZipCode(const QString &value) {zipCode = value;}

    QString getCountry() const {return country;}
    void setCountry(const QString &value) {country = value;}

    QString getStreetNumber() const {return streetNumber;}
    void setStreetNumber(const QString &value) {streetNumber = value;}

private:
    int user_id;
    QString city;
    QString state;
    QString zipCode;
    QString country;
    QString streetNumber;

};


namespace Ui {
class AddressDTO;
}

class AddressDTO : public QDialog
{
    Q_OBJECT

public:
    explicit AddressDTO(QWidget *parent = nullptr);
    ~AddressDTO();
    Address getDTO() {return _address;}

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();


    void on_zipcodeComboBox_currentIndexChanged(const QString &arg1);

    void on_zipcodeComboBox_currentIndexChanged(int index);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_redoAvailable(bool b);

    void on_textEdit_textChanged();

private:
    Ui::AddressDTO *ui;
    Address _address;
    QStringList countryItems;
};

#endif // ADDRESSDTO_H
