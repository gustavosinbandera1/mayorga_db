#ifndef ORDERFORM_H
#define ORDERFORM_H
#include <QMainWindow>
#include "detailsDialog.h"

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

  bool saveOrder(QList<DTODetails> orderItems, QString paymentMethod);
  DbManager* _dbM;
  QAction *printAction;
  QTabWidget *lettersTab;
};
#endif  // ORDERFORM_H
