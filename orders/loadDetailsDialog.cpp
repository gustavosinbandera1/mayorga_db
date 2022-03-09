#include "loadDetailsDialog.h"

#include <QtWidgets>

#include "login.h"

DetailsDialog::DetailsDialog(DbManager *dbm, const QString &title,
                             QWidget *parent)
    : QDialog(parent) {
  _dbM = dbm;
  isEmpty = true;
  quantityDelegate = new QuantityTotalDelegate(this);
  nameLabel = new QLabel(tr("Name:"));
  addressLabel = new QLabel(tr("Address:"));
  addressLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  nameEdit = new QLineEdit;
  nameEdit->setReadOnly(true);
  nameEdit->setText(UserData::userName);
  addressEdit = new QTextEdit;
  paymentChoice = new QComboBox();
  paymentChoice->addItems({"visa", "mastercard", "cash"});

  QSqlQuery qry(_dbM->db());
  qry.prepare(
      "SELECT address_id, city, state, street_number, "
      "address_type "
      "from customer_address "
      "JOIN customer ON customer_address.fk_customer_id=customer.customer_id "
      "JOIN address ON customer_address.fk_address_id=address.address_id "
      "WHERE customer_address.fk_customer_id=:id"

  );
  qry.bindValue(":id", UserData::userId);
  qry.exec();

  qDebug() << "error output " << qry.lastError().text();

  qDebug() << "Size: " << qry.size();
  qDebug() << "--> " << qry.next();

  qDebug() << "DATA: " << qry.record().value("street_number").toString();
  addressEdit->setPlainText(qry.record().value("street_number").toString());
  //}
  setupItemsTable();

  buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

  connect(itemsTable, &QTableWidget::itemChanged,
          []() { qDebug() << "Item changed .........................."; });

  connect(itemsTable, SIGNAL(itemChanged(QTableWidgetItem *)), this,
          SLOT(on_table_itemChanged(QTableWidgetItem *)));
  connect(buttonBox, &QDialogButtonBox::accepted, this, &DetailsDialog::verify);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &DetailsDialog::reject);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(nameLabel, 0, 0);
  mainLayout->addWidget(nameEdit, 0, 1);
  mainLayout->addWidget(addressLabel, 1, 0);
  mainLayout->addWidget(addressEdit, 1, 1);
  mainLayout->addWidget(itemsTable, 0, 2, 2, 1);
  mainLayout->addWidget(paymentChoice, 2, 1, 1, 2);
  mainLayout->addWidget(buttonBox, 3, 0, 1, 3);
  setLayout(mainLayout);

  setWindowTitle(title);
}
//----------------------//
//----------------------//
QList<DTODetails> DetailsDialog::orderItems() {
  QList<DTODetails> _orderList;
  for (int row = 0; row < _items.count(); ++row) {
    DTODetails item;

    QString name = itemsTable->item(row, 0)->text();
    item.productName = name;

    int quantity = itemsTable->item(row, 1)->data(Qt::DisplayRole).toInt();
    item.quantity = qMax(0, quantity);

    double price = itemsTable->item(row, 2)->data(Qt::DisplayRole).toDouble();
    item.price = price;

    double total = itemsTable->item(row, 3)->data(Qt::DisplayRole).toDouble();
    item.purchase = total;

    item.sku = itemsTable->item(row, 4)->data(Qt::DisplayRole).toInt();
    if (item.quantity > 0) {
      _orderList.append(item);
    }
  }
  if (_orderList.count() > 0) isEmpty = false;
  return _orderList;
}

//----------------------//
//----------------------//
QString DetailsDialog::getSenderName() const { return nameEdit->text(); }
//----------------------//
//----------------------//
QString DetailsDialog::getSenderAddress() const {
  return addressEdit->toPlainText();
}
//----------------------//
//----------------------//
QString DetailsDialog::getPaymentMethod() const {
  return paymentChoice->currentText();
}

//----------------------//
//----------------------//
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
//----------------------//
//----------------------//
void DetailsDialog::setupItemsTable() {
  QString command = QString("SELECT name,price,sku FROM %1 ").arg("products");
  QSqlQuery qry;  //(_dbM->db());
  qry.prepare(command);
  qry.exec();

  DTODetails tmpDTO;
  while (qry.next()) {
    tmpDTO.sku = qry.record().value("sku").toInt();
    tmpDTO.productName = qry.record().value("name").toString();
    tmpDTO.price = qry.record().value("price").toDouble();
    _items.push_back(tmpDTO);
  }

  itemsTable = new QTableWidget(_items.count(), 5, this);

  itemsTable->setItemDelegateForColumn(1, quantityDelegate);
  itemsTable->setHorizontalHeaderLabels(
      {"Product", "Quantity", "Price", "Total", "sku"});

  for (int row = 0; row < _items.count(); ++row) {
    QTableWidgetItem *name = new QTableWidgetItem(_items[row].productName);
    name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    itemsTable->setItem(row, 0, name);

    QTableWidgetItem *quantity = new QTableWidgetItem("0");
    itemsTable->setItem(row, 1, quantity);

    QTableWidgetItem *price = new QTableWidgetItem(QString::number(
        _items[row].price));  // this value will need to be dinamically load
    itemsTable->setItem(row, 2, price);

    price->setFlags(price->flags() ^ Qt::ItemIsEditable);

    QTableWidgetItem *totalPrice = new QTableWidgetItem("0");
    itemsTable->setItem(row, 3, totalPrice);
    totalPrice->setFlags(totalPrice->flags() ^ Qt::ItemIsEditable);

    QTableWidgetItem *sku =
        new QTableWidgetItem(QString::number(_items[row].sku));
    itemsTable->setItem(row, 4, sku);
    sku->setFlags(sku->flags() ^ Qt::ItemIsEditable);

    itemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    itemsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  }
}
//----------------------//
//----------------------//
void DetailsDialog::on_table_itemChanged(QTableWidgetItem *item) {
  if (item->column() == 1) {
    qDebug() << "Going to update others cells .............";
    int quantity = itemsTable->item(item->row(), 1)->text().toInt();
    double total;
    double price = itemsTable->item(item->row(), 2)->text().toDouble();
    total = (double)(price * quantity);
    itemsTable->item(item->row(), 3)->setText(QString::number(total));
  }
}
//----------------------//
//----------------------//
void DetailsDialog::on_actionSave_triggered() {
  qDebug() << "Action: "
           << "on_actionSave_triggered";
}

void DetailsDialog::sendQuery() {
  QSqlQuery query;
  query.prepare(
      "SELECT address_id, city, state, street_number, "
      "address_type , country_name, country_id , zipcode "
      "from customer_address "
      "JOIN customer ON customer_address.fk_customer_id=customer.customer_id "
      "JOIN address ON customer_address.fk_address_id=address.address_id "
      "JOIN country ON address.fk_country_id=country.country_id "
      "WHERE customer_address.fk_customer_id=:id");
  query.bindValue(":id", UserData::userId);

  qDebug() << "error output " << query.lastError().text();

  // ui->addressTableView->setColumnHidden(6, true);
  // ui->addressTableView->setColumnHidden(7, true);
}
