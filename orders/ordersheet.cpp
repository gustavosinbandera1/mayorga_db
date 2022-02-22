#include "ordersheet.h"

#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QtWidgets>

#include "ui_ordersheet.h"

//! [0]
OrderSheet::OrderSheet(const QString &title, QWidget *parent)
    : QDialog(parent)  //,
                       // ui(new Ui::OrderSheet)
{
  // ui->setupUi(this);
  nameLabel = new QLabel(tr("Name"));
  addressLabel = new QLabel(tr("Address"));
  addressLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);

  nameEdit = new QLineEdit;
  addressEdit = new QTextEdit;

  setupItemsTable();
  buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  // connect(buttonBox, &QDialogButtonBox::accepted, this, &OrderSheet::verify);
  // connect(buttonBox, &QDialogButtonBox::rejected, this, &OrderSheet::reject);
  connect(buttonBox, SIGNAL(QDialogButtonBox::accepted), this,
          SLOT(OrderSheet::verify));
  connect(buttonBox, SIGNAL(QDialogButtonBox::rejected), this,
          SLOT(OrderSheet::reject));
  //! [0]

  //! [1]
  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addWidget(nameLabel, 0, 0);
  mainLayout->addWidget(nameEdit, 0, 1);
  mainLayout->addWidget(addressLabel, 1, 0);
  mainLayout->addWidget(addressEdit, 1, 1);
  mainLayout->addWidget(itemsTable, 0, 2, 2, 1);
  mainLayout->addWidget(buttonBox, 3, 0, 1, 3);

  setWindowTitle(title);
}
//! [1]

//! [2]
void OrderSheet::setupItemsTable() {
  items << tr("T-shirt") << tr("Badge") << tr("Reference book")
        << tr("Coffee cup");
  itemsTable = new QTableWidget(items.count(), 2);
  for (int row = 0; row < items.count(); ++row) {
    QTableWidgetItem *name = new QTableWidgetItem(items[row]);
    name->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    itemsTable->setItem(row, 1, name);

    QTableWidgetItem *quantity = new QTableWidgetItem("1");
    itemsTable->setItem(row, 1, quantity);
  }
}
//! [2]

//! [3]
QList<QPair<QString, int>> OrderSheet::orderItems() {
  QList<QPair<QString, int>> orderList;
  for (int row = 0; row < items.count(); ++row) {
    QPair<QString, int> item;
    item.first = itemsTable->item(row, 0)->text();
    int quantity = itemsTable->item(row, 1)->data(Qt::DisplayRole).toUInt();
    item.second = qMax(0, quantity);
    orderList.append(item);
  }
  return orderList;
}
//! [3]

//! [4]
QString OrderSheet::senderName() const { return nameEdit->text(); }
//! [4]

//! [5]
QString OrderSheet::senderAddress() const { return addressEdit->toPlainText(); }

//! [5]

//! [6]
void OrderSheet::verify() {
  if (!nameEdit->text().isEmpty() && !addressEdit->toPlainText().isEmpty()) {
    accept();
    return;
  }
  QMessageBox::StandardButton answer;
      answer = QMessageBox::warning(this, tr("Incomplete Form"),
          tr("The form does not contain all the necessary information.\n"
             "Do you want to discard it?"),
          QMessageBox::Yes | QMessageBox::No);

      if (answer == QMessageBox::Yes)
          reject();
}
//! [6]


OrderSheet::~OrderSheet() {
    qInfo()<<tr("Destroying OrderSheet");
  // delete ui;
}