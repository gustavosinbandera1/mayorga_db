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
  ui->addressTableView->setColumnHidden(3, true);
  ui->addressTableView->setAlternatingRowColors(true);

  ui->addressTableView->setSortingEnabled(true);
  ui->addressTableView->sortByColumn(0, Qt::AscendingOrder);
  ui->addressTableView->reset();

  ui->addressIDLineEdit->setDisabled(true);

}
//---------------------
AddressView::~AddressView() {
  qDebug() << "Destroying AddressView";
  delete ui;
}

void AddressView::updateAddressModel() {
  ui->addressTableView->setModel(aModel->updateModel());
  aModel->setHeaders();
  ui->addressTableView->setColumnHidden(3, true);
}

void AddressView::on_addressTableView_clicked(const QModelIndex &index)
{
    qDebug()<< "Cell clicked " ;
    QSqlTableModel *tmpModel = aModel->getAddressModel();
//    ui->addressLineEdit->setText(tmpModel->index(index.row(),0).data().toString());
//    ui->cityLineEdit->setText(tmpModel->index(index.row(),1).data().toString());
//    ui->stateLineEdit->setText(tmpModel->index(index.row(),2).data().toString());

    ui->addressIDLineEdit->setText(tmpModel->record(index.row()).value("address_id").toString());
    ui->cityLineEdit->setText(tmpModel->record(index.row()).value("city").toString());
    ui->stateLineEdit->setText(tmpModel->record(index.row()).value("state").toString());

    ui->streetNumberTextEdit->setPlainText(tmpModel->record(index.row()).value("street_number").toString());

    ui->countryLineEdit->setText(tmpModel->record(index.row()).value("fk_country_id").toString());
    ui->addressTypeLineEdit->setText(tmpModel->record(index.row()).value("address_type").toString());
}
