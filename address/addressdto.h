#ifndef ADDRESSDTO_H
#define ADDRESSDTO_H

#include <QDialog>

class Address {
public:
    Address(QString city,
            QString state,
            QString zipcode,
            QString country);

    Address(){};
    QString getCity() const {return city;}
    void setCity(const QString &value) {city = value;}

    QString getState() const {return state;}
    void setState(const QString &value) {state = value;}

    QString getZipCode() const {return zipCode;}
    void setZipCode(const QString &value) {zipCode = value;}

    QString getCountry() const {return country;}
    void setCountry(const QString &value) {country = value;}

private:
    QString city;
    QString state;
    QString zipCode;
    QString country;

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


private:
    Ui::AddressDTO *ui;
    Address _address;
};

#endif // ADDRESSDTO_H
