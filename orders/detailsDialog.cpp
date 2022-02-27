#include "detailsDialog.h"
#include <QtWidgets>
#include "login.h"


DetailsDialog::DetailsDialog(DbManager *dbm, const QString &title,
                             QWidget *parent)
    : QDialog(parent) {
  _dbM = dbm;
  spinBoxDelegate = new SpinboxDelegate(this);
  nameLabel = new QLabel(tr("Name:"));
  addressLabel = new QLabel(tr("Address:"));
  addressLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  offersCheckBox =
      new QCheckBox(tr("Send information about products and "
                       "special offers"));
  nameEdit = new QLineEdit;
  nameEdit->setReadOnly(true);
  nameEdit->setText(UserData::userName);

  // pWidget = new QTableWidget(5, 6);
  addressEdit = new QTextEdit;
  setupItemsTable();
  // populateTable(5, 6);

  buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  connect(buttonBox, &QDialogButtonBox::accepted, this, &DetailsDialog::verify);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &DetailsDialog::reject);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(nameLabel, 0, 0);
  mainLayout->addWidget(nameEdit, 0, 1);
  mainLayout->addWidget(addressLabel, 1, 0);
  mainLayout->addWidget(addressEdit, 1, 1);
  mainLayout->addWidget(itemsTable, 0, 2, 2, 1);
  // mainLayout->addWidget(pWidget, 0, 2, 2, 1);
  mainLayout->addWidget(offersCheckBox, 2, 1, 1, 2);
  mainLayout->addWidget(buttonBox, 3, 0, 1, 3);
  setLayout(mainLayout);

  setWindowTitle(title);
}
//---------------------
// void DetailsDialog::setupItemsTable() {
//  items << tr("T-shirt") << tr("Badge") << tr("Reference book")
//        << tr("Coffee cup");

//  itemsTable = new QTableWidget(items.count(), 3);

//  for (int row = 0; row < items.count(); ++row) {
//    QTableWidgetItem *name = new QTableWidgetItem(items[row]);
//    name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
//    itemsTable->setItem(row, 0, name);
//    QTableWidgetItem *quantity = new QTableWidgetItem("1");
//    itemsTable->setItem(row, 1, quantity);
//  }
//}
//---------------------
QList<QPair<QString, int> > DetailsDialog::orderItems() {
  QList<QPair<QString, int> > orderList;

  for (int row = 0; row < items.count(); ++row) {
    QPair<QString, int> item;
    item.first = itemsTable->item(row, 0)->text();
    int quantity = itemsTable->item(row, 1)->data(Qt::DisplayRole).toInt();
    item.second = qMax(0, quantity);
    orderList.append(item);
  }
  return orderList;
}
//---------------------
QString DetailsDialog::senderName() const { return nameEdit->text(); }
//---------------------
QString DetailsDialog::senderAddress() const {
  return addressEdit->toPlainText();
}
//---------------------
bool DetailsDialog::sendOffers() { return offersCheckBox->isChecked(); }
//---------------------
void DetailsDialog::verify() {
  if (!nameEdit->text().isEmpty() && !addressEdit->toPlainText().isEmpty()) {
    accept();
    return;
  }

  QMessageBox::StandardButton answer;
  answer = QMessageBox::warning(
      this, tr("Incomplete Form"),
      tr("The form does not contain all the necessary information.\n"
         "Do you want to discard it?"),
      QMessageBox::Yes | QMessageBox::No);

  if (answer == QMessageBox::Yes) reject();
}

// void DetailsDialog::populateTable(int rows, int columns) {
//  // QTableWidget *pWidget = new QTableWidget( rows, columns );

//  for (int row = 0; row < rows; row++) {
//    for (int column = 0; column < columns; column++) {
//      QString sItem = QString::number(row + column);

//      QVariant oVariant(sItem);

//      // allocate the widget item
//      QTableWidgetItem *poItem = new QTableWidgetItem();
//      poItem->setData(Qt::DisplayRole, oVariant);
//      pWidget->setItem(row, column, poItem);
//    }
//  }
//}

void DetailsDialog::setupItemsTable() {
  QString command = QString("SELECT name,price FROM %1 ").arg("products");
  QSqlQuery qry;//(_dbM->db());
  qry.prepare(command);
  qry.exec();

  while (qry.next()) {
    qDebug() << "product name --> " << qry.record().value("name").toString();
    qDebug() << "product price --> " << qry.record().value("price").toDouble();
    items.push_back(qry.record().value("name").toString());
  }

  itemsTable = new QTableWidget(items.count(), 4);


  itemsTable->setItemDelegateForColumn(1, spinBoxDelegate);
  itemsTable->setHorizontalHeaderLabels(
      {"Product", "Quantity", "Price", "Total"});
  for (int row = 0; row < items.count(); ++row) {

    QTableWidgetItem *name = new QTableWidgetItem(items[row]);
    name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    itemsTable->setItem(row, 0, name);

    QTableWidgetItem *quantity = new QTableWidgetItem("0");
    itemsTable->setItem(row, 1, quantity);

    QTableWidgetItem *price = new QTableWidgetItem("1000");  // this value will need to be dinamically load
    itemsTable->setItem(row, 2, price);

    price->setFlags(price->flags() ^ Qt::ItemIsEditable);


    QTableWidgetItem *totalPrice = new QTableWidgetItem("0");  // this value will need to be dinamically load
    itemsTable->setItem(row, 3, totalPrice);
    totalPrice->setFlags(totalPrice->flags() ^ Qt::ItemIsEditable);
  }
}
//---------------------
