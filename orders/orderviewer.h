#ifndef ORDERVIEWER_H
#define ORDERVIEWER_H

#include <QWidget>

namespace Ui {
class OrderViewer;
}

class OrderViewer : public QWidget
{
    Q_OBJECT

public:
    explicit OrderViewer(QWidget *parent = nullptr);
    ~OrderViewer();

private:
    Ui::OrderViewer *ui;
};

#endif // ORDERVIEWER_H
