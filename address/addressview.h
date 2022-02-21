#ifndef ADDRESSVIEW_H
#define ADDRESSVIEW_H

#include <QWidget>
#include "dbmanager.h"
namespace Ui {
class AddressView;
}

class AddressView : public QWidget
{
    Q_OBJECT

public:
    explicit AddressView(DbManager* mdb, QWidget *parent = nullptr);
    ~AddressView();

private:
    Ui::AddressView *ui;
};

#endif // ADDRESSVIEW_H
