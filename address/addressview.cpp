#include "addressview.h"

#include "addressmodel.h"
#include "ui_addressview.h"

AddressView::AddressView(DbManager* mdb, QWidget* parent)
    : QWidget(parent), ui(new Ui::AddressView) {
  ui->setupUi(this);
  aModel = new AddressModel(mdb, this);
  ui->addressTableView->setModel(aModel->getAddressModel());
  ui->addressTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->addressTableView->setVisible(true);
  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->addressTableView->reset();
}
//---------------------
AddressView::~AddressView() {
  qDebug() << "Destroying AddressView";
  delete ui;
}

void AddressView::updateAddressModel() {
  ui->addressTableView->setModel(aModel->updateModel());
}
