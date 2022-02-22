#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QMainWindow>

// namespace Ui {
// class OrderForm;
//}
QT_BEGIN_NAMESPACE
class QAction;
class QTabWidget;
QT_END_NAMESPACE

//! [0]
class OrderForm : public QMainWindow {
  Q_OBJECT

 public:
  explicit OrderForm(QWidget *parent = nullptr);
  void createSample();
  ~OrderForm();

 public slots:
  void openDialog();
  void printFile();

 private:
  // Ui::OrderForm *ui;
  void createLetter(const QString &name, const QString &address,
                    QList<QPair<QString, int>> orderItems);
  QAction *printAction;
  QTabWidget *lettersTab;
};
//! [0]
#endif  // ORDERFORM_H
