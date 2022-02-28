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
  void createLetter(const QString &name, const QString &address,
                    QList<DTODetails> orderItems);
  DbManager* _dbM;
  QAction *printAction;
  QTabWidget *lettersTab;
};
#endif  // ORDERFORM_H
