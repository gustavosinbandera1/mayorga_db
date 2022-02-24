#ifndef ADDRESSVIEW_H
#define ADDRESSVIEW_H

#include <QWidget>
#include "dbmanager.h"

class AddressModel;
namespace Ui {
class AddressView;
}

class AddressView : public QWidget
{
    Q_OBJECT

public:
    explicit AddressView(DbManager* mdb, QWidget *parent = nullptr);
    ~AddressView();
    void updateAddressModel();

private:
    Ui::AddressView *ui;
    AddressModel* aModel;
};

#endif // ADDRESSVIEW_H
