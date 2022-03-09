#include "orderviewer.h"
#include "ui_orderviewer.h"

OrderViewer::OrderViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderViewer)
{
    ui->setupUi(this);
}

OrderViewer::~OrderViewer()
{
    delete ui;
}
