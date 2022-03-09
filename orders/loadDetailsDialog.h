
#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QComboBox>
#include <QDialog>
#include <QList>
#include <QPair>
#include <QTableWidget>

#include "dbmanager.h"
#include "quantitytotaldelegate.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTableWidget;
class QTextEdit;
class QWidget;
QT_END_NAMESPACE

struct DTODetails {
  int price;
  QString productName;
  int quantity;
  int purchase;
  int sku;
};

class DetailsDialog : public QDialog {
  Q_OBJECT

 public:
  DetailsDialog(DbManager *dbm, const QString &title, QWidget *parent);

 public slots:
  void verify();

 public:
  QList<DTODetails> orderItems();
  QString getSenderName() const;
  QString getSenderAddress() const;
  bool sendOffers();
  QString getPaymentMethod() const;
  bool isEmpty;

 private:
  void setupItemsTable();

  QLabel *nameLabel;
  QLabel *addressLabel;
  QLineEdit *nameEdit;
  QList<DTODetails> _items;
  QTableWidget *itemsTable;
  QTextEdit *addressEdit;
  QDialogButtonBox *buttonBox;
  QComboBox *paymentChoice;

  void populateTable(int rows, int colums);
  DbManager *_dbM;

  QuantityTotalDelegate *quantityDelegate;

 private slots:
  void on_actionSave_triggered();
  void on_table_itemChanged(QTableWidgetItem *item);
};

#endif  // DETAILSDIALOG_H
