#ifndef ORDERSVIEW_H
#define ORDERSVIEW_H

#include <QWidget>

namespace Ui {
class OrdersView;
}

class OrdersView : public QWidget {
  Q_OBJECT

 public:
  explicit OrdersView(QWidget *parent = nullptr);
  ~OrdersView();

 private:
  Ui::OrdersView *ui;
};

#endif  // ORDERSVIEW_H
