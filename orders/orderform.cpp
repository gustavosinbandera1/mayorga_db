#include "orderform.h"
#include "ui_orderform.h"
#include "ordersheet.h"

// ! [0]
OrderForm::OrderForm(QWidget *parent)
    : QMainWindow(parent) {

    QMenu *fileMenu = new QMenu(tr("&File"), this);

    QAction *newAction = fileMenu->addAction(tr("&New..."));
    newAction->setShortcuts(QKeySequence::New);

    printAction = fileMenu->addAction(tr("&Print..."), this, &OrderForm::printFile);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setEnabled(false);

    QAction *quitAction = fileMenu->addAction(tr("E&xit"));
    quitAction->setShortcuts(QKeySequence::Quit);


    menuBar()->addMenu(fileMenu);

    lettersTab = new QTabWidget;
    connect(newAction, &QAction::triggered, this, &OrderForm::openDialog);
    connect(quitAction, &QAction::triggered, this, &OrderForm::close);

    setCentralWidget(lettersTab);
}

OrderForm::~OrderForm() {
    // delete ui;
}

void OrderForm::openDialog()
{

}

void OrderForm::printFile()
{

}
