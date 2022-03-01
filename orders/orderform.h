#ifndef ORDERFORM_H
#define ORDERFORM_H
#include <QMainWindow>
#include "loadDetailsDialog.h"

QT_BEGIN_NAMESPACE
class QAction;
class QTabWidget;
class DbManager;
QT_END_NAMESPACE


class OrderForm : public QMainWindow {
  Q_OBJECT

 public:
  explicit OrderForm(DbManager* dbm, QWidget *parent = nullptr);
  void createSample();
  ~OrderForm();

 public slots:
  void openDialog();
  void printFile();

 private:
  void createLetter(QString &&name, QString &&address,
                    QList<DTODetails> &&orderItems);

  int saveOrder(const QList<DTODetails> &orderItems, QString &&paymentMethod);
  void saveItems(const QList<DTODetails> &orderItems, int orderId);
  DbManager* _dbM;
  QAction *printAction;
  QTabWidget *lettersTab;
};
#endif  // ORDERFORM_H
