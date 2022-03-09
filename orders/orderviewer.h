#ifndef ORDERVIEWER_H
#define ORDERVIEWER_H

#include <queryModel.h>

#include <QDialog>
#include <QWidget>

#include "dbmanager.h"

namespace Ui {

class OrderViewer;
}

class OrderViewer : public QDialog {
  Q_OBJECT

 public:
  explicit OrderViewer(DbManager* _dbm, int orderId, QWidget* parent = nullptr);
  ~OrderViewer();
  void sendQuery();

 private slots:

  void on_okButton_accepted();

 private:
  Ui::OrderViewer* ui;
  DbManager* _dbM;
  QueryModel* model;
  int orderID;
};

#endif  // ORDERVIEWER_H
