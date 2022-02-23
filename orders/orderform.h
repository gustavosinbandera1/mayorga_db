#ifndef ORDERFORM_H
#define ORDERFORM_H
#include <QMainWindow>

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
                    QList<QPair<QString,int> > orderItems,
                    bool sendOffers);
  DbManager* _dbM;
  QAction *printAction;
  QTabWidget *lettersTab;
};
#endif  // ORDERFORM_H
