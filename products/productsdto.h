#ifndef PRODUCTSDTO_H
#define PRODUCTSDTO_H

#include <QDialog>

/**
 * @brief The ProductsDTO class
 * class for handling the UI Dialog for add new products, here we can define default behavior
 *
*/

class Product {
public:
    Product(QString sku,
            QString description,
            QString price,
            QString weight);

    Product(){};

    QString getSku() const {return sku;}
    void setSku(const QString &value) {sku = value;}

    QString getName() const {return name;}
    void setName(const QString &value) {name = value;}

    QString getDescription() const {return description;}
    void setDescription(const QString &value) {description = value;}

    QString getPrice() const {return price;}
    void setPrice(const QString &value) {price = value;}

    QString getWeight() const {return weight;}
    void setWeight(const QString &value) {weight = value;}

private:
    QString sku;
    QString name;
    QString description;
    QString price;
    QString weight;

};

namespace Ui {
class ProductsDTO;
}

class ProductsDTO : public QDialog
{
    Q_OBJECT

public:
    explicit ProductsDTO(QWidget *parent = nullptr);
    ~ProductsDTO();
    Product getDTO(){return _product;}

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ProductsDTO *ui;
    Product _product;
};

#endif // PRODUCTSDTO_H
