#ifndef ORDERSHEET_H
#define ORDERSHEET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QTableWidget;
class QTextEdit;
class QDialogButtonBox;
QT_END_NAMESPACE

// namespace Ui {
// class OrderSheet;
//}

class OrderSheet : public QDialog {
  Q_OBJECT

 public slots:
  void verify();

 public:
  explicit OrderSheet(const QString &title, QWidget *parent = nullptr);
  ~OrderSheet();

  QList<QPair<QString, int> > orderItems();
  QString senderName() const;
  QString senderAddress() const;

 private:
  QLabel *nameLabel;
  QLabel *addressLabel;
  QLineEdit *nameEdit;
  QTextEdit *addressEdit;
  QStringList items;
  QTableWidget *itemsTable;
  QDialogButtonBox *buttonBox;

  void setupItemsTable();

  // private : Ui::OrderSheet *ui;
};

#endif  // ORDERSHEET_H
