#ifndef PRODUCTSDTO_H
#define PRODUCTSDTO_H

#include <QDialog>

/**
 * @brief The ProductsDTO class
 * class for handling the UI Dialog for add new products, here we can define default behavior
 *
*/

class ProductDataObject {
public:
    ProductDataObject(QString sku,
            QString description,
            QString price,
            QString weight);

    ProductDataObject(){};

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
    QString sku = "";
    QString name= "";
    QString description ="";
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
    ProductDataObject getDTO(){return product;} //to remove just test
    ProductDataObject product;
    void updateForm();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ProductsDTO *ui;

};

#endif // PRODUCTSDTO_H
