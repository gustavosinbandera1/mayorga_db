#include "detailsDialog.h"

#include <QtWidgets>

#include "login.h"

DetailsDialog::DetailsDialog(DbManager *dbm, const QString &title,
                             QWidget *parent)
    : QDialog(parent) {
  _dbM = dbm;
  quantityDelegate = new QuantityTotalDelegate(this);
  nameLabel = new QLabel(tr("Name:"));
  addressLabel = new QLabel(tr("Address:"));
  addressLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  nameEdit = new QLineEdit;
  nameEdit->setReadOnly(true);
  nameEdit->setText(UserData::userName);

  addressEdit = new QTextEdit;

  QSqlQuery qry(_dbM->db());
  QString query = "SELECT * from customer_address";

  qDebug() << "STATUS--->>>> "
           << qry.exec(QString(
                  "SELECT * from customer_address"
                  " JOIN address ON"
                  " customer_address.fk_address_id = address.address_id"));
  // while (qry.next()) {
  // select * from customer_address join address ON
  // customer_address.fk_address_id=address.address_id  JOIN customer  ON
  // customer_address.fk_customer_id = customer.customer_id ;
  qry.first();
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

  mainLayout->addWidget(buttonBox, 3, 0, 1, 3);
  setLayout(mainLayout);

  setWindowTitle(title);
}


QList<DTODetails> DetailsDialog::orderItems() const {
  QList<DTODetails> _orderList;
  for (int row = 0; row < _items.count(); ++row) {
    DTODetails item;

    QString name = itemsTable->item(row, 0)->text();
    item.name = name;

    int quantity = itemsTable->item(row, 1)->data(Qt::DisplayRole).toInt();
    item.quantity = qMax(0, quantity);

    int price =  itemsTable->item(row, 2)->data(Qt::DisplayRole).toInt();
    item.price = price;


    int total =  itemsTable->item(row, 3)->data(Qt::DisplayRole).toInt();
    item.total = total;

    if (item.quantity > 0)
        _orderList.append(item);
  }
  return _orderList;
}


//---------------------
QString DetailsDialog::getSenderName() const { return nameEdit->text(); }
//---------------------
QString DetailsDialog::getSenderAddress() const {
  return addressEdit->toPlainText();
}
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

void DetailsDialog::setupItemsTable() {
  QString command = QString("SELECT name,price FROM %1 ").arg("products");
  QSqlQuery qry;  //(_dbM->db());
  qry.prepare(command);
  qry.exec();

  while (qry.next()) {
    _items.push_back(QPair<QString, int>(qry.record().value("name").toString(),
                                         qry.record().value("price").toInt()));
  }

  itemsTable = new QTableWidget(_items.count(), 4, this);

  itemsTable->setItemDelegateForColumn(1, quantityDelegate);
  itemsTable->setHorizontalHeaderLabels(
      {"Product", "Quantity", "Price", "Total"});

  for (int row = 0; row < _items.count(); ++row) {
    QTableWidgetItem *name = new QTableWidgetItem(_items[row].first);
    name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    itemsTable->setItem(row, 0, name);

    QTableWidgetItem *quantity = new QTableWidgetItem("0");
    itemsTable->setItem(row, 1, quantity);

    QTableWidgetItem *price = new QTableWidgetItem(QString::number(
        _items[row].second));  // this value will need to be dinamically load
    itemsTable->setItem(row, 2, price);

    price->setFlags(price->flags() ^ Qt::ItemIsEditable);

    QTableWidgetItem *totalPrice = new QTableWidgetItem("0");
    itemsTable->setItem(row, 3, totalPrice);
    totalPrice->setFlags(totalPrice->flags() ^ Qt::ItemIsEditable);
  }
}
//---------------------
void DetailsDialog::on_table_itemChanged(QTableWidgetItem *item) {
  if (item->column() == 1) {
    int quantity = itemsTable->item(item->row(), 1)->text().toInt();
    int total;
    int price = itemsTable->item(item->row(), 2)->text().toInt();
    total = price * quantity;
    qDebug() << "Total: " << total;
    // total
    itemsTable->item(item->row(), 3)->setText(QString::number(total));
  }
}

void DetailsDialog::on_actionSave_triggered() {
  qDebug() << "Action: "
           << "on_actionSave_triggered";
}
