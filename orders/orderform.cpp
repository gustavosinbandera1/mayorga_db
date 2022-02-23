#include "orderform.h"

#include <QDate>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextFrame>
#include <QTextTable>

#include "dbmanager.h"
#include "detailsDialog.h"
#include "ui_orderform.h"

OrderForm::OrderForm(DbManager *dbm, QWidget *parent)
    : QMainWindow(parent), _dbM(dbm) {
  QMenu *fileMenu = new QMenu(tr("&File"), this);

  QAction *newAction = fileMenu->addAction(tr("&New..."));
  newAction->setShortcuts(QKeySequence::New);

  printAction =
      fileMenu->addAction(tr("&Print..."), this, &OrderForm::printFile);
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
//---------------------
void OrderForm::createLetter(const QString &name, const QString &address,
                             QList<QPair<QString, int> > orderItems,
                             bool sendOffers) {
  QTextEdit *editor = new QTextEdit;
  int tabIndex = lettersTab->addTab(editor, name);
  lettersTab->setCurrentIndex(tabIndex);

  QTextCursor cursor(editor->textCursor());
  cursor.movePosition(QTextCursor::Start);

  QTextFrame *topFrame = cursor.currentFrame();
  QTextFrameFormat topFrameFormat = topFrame->frameFormat();
  topFrameFormat.setPadding(16);
  topFrame->setFrameFormat(topFrameFormat);

  QTextCharFormat textFormat;
  QTextCharFormat boldFormat;
  boldFormat.setFontWeight(QFont::Bold);

  QTextFrameFormat referenceFrameFormat;
  referenceFrameFormat.setBorder(1);
  referenceFrameFormat.setPadding(8);
  referenceFrameFormat.setPosition(QTextFrameFormat::FloatRight);
  referenceFrameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 40));
  cursor.insertFrame(referenceFrameFormat);

  cursor.insertText("A company", boldFormat);
  cursor.insertBlock();
  cursor.insertText("321 City Street");
  cursor.insertBlock();
  cursor.insertText("Industry Park");
  cursor.insertBlock();
  cursor.insertText("Another country");

  cursor.setPosition(topFrame->lastPosition());

  cursor.insertText(name, textFormat);
  const QStringList lines = address.split('\n');
  for (const QString &line : lines) {
    cursor.insertBlock();
    cursor.insertText(line);
  }
  cursor.insertBlock();
  cursor.insertBlock();

  QDate date = QDate::currentDate();
  cursor.insertText(tr("Date: %1").arg(date.toString("d MMMM yyyy")),
                    textFormat);
  cursor.insertBlock();

  QTextFrameFormat bodyFrameFormat;
  bodyFrameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
  cursor.insertFrame(bodyFrameFormat);

  cursor.insertText(tr("I would like to place an order for the following "
                       "items:"),
                    textFormat);
  cursor.insertBlock();

  cursor.insertBlock();

  QTextTableFormat orderTableFormat;
  orderTableFormat.setAlignment(Qt::AlignHCenter);
  QTextTable *orderTable = cursor.insertTable(1, 2, orderTableFormat);

  QTextFrameFormat orderFrameFormat = cursor.currentFrame()->frameFormat();
  orderFrameFormat.setBorder(1);
  cursor.currentFrame()->setFrameFormat(orderFrameFormat);

  cursor = orderTable->cellAt(0, 0).firstCursorPosition();
  cursor.insertText(tr("Product"), boldFormat);
  cursor = orderTable->cellAt(0, 1).firstCursorPosition();
  cursor.insertText(tr("Quantity"), boldFormat);

  for (int i = 0; i < orderItems.count(); ++i) {
    QPair<QString, int> item = orderItems[i];
    int row = orderTable->rows();

    orderTable->insertRows(row, 1);
    cursor = orderTable->cellAt(row, 0).firstCursorPosition();
    cursor.insertText(item.first, textFormat);
    cursor = orderTable->cellAt(row, 1).firstCursorPosition();
    cursor.insertText(QString("%1").arg(item.second), textFormat);
  }

  cursor.setPosition(topFrame->lastPosition());

  cursor.insertBlock();

  cursor.insertText(
      tr("Please update my records to take account of the "
         "following privacy information:"));
  cursor.insertBlock();

  QTextTable *offersTable = cursor.insertTable(2, 2);

  cursor = offersTable->cellAt(0, 1).firstCursorPosition();
  cursor.insertText(tr("I want to receive more information about your "
                       "company's products and special offers."),
                    textFormat);
  cursor = offersTable->cellAt(1, 1).firstCursorPosition();
  cursor.insertText(tr("I do not want to receive any promotional information "
                       "from your company."),
                    textFormat);

  if (sendOffers)
    cursor = offersTable->cellAt(0, 0).firstCursorPosition();
  else
    cursor = offersTable->cellAt(1, 0).firstCursorPosition();

  cursor.insertText("X", boldFormat);

  cursor.setPosition(topFrame->lastPosition());
  cursor.insertBlock();
  cursor.insertText(tr("Sincerely,"), textFormat);
  cursor.insertBlock();
  cursor.insertBlock();
  cursor.insertBlock();
  cursor.insertText(name);

  printAction->setEnabled(true);
}
//---------------------
void OrderForm::createSample() {
  DetailsDialog dialog("Dialog with default values", this);
  createLetter("Mr. Smith", "12 High Street\nSmall Town\nThis country",
               dialog.orderItems(), true);
}
//---------------------
OrderForm::~OrderForm() {
  // delete ui;
}
//---------------------
void OrderForm::openDialog() {
  DetailsDialog dialog(tr("Enter customer Details"), this);
  if (dialog.exec() == QDialog::Accepted) {
    createLetter(dialog.senderName(), dialog.senderAddress(),
                 dialog.orderItems(), dialog.sendOffers());
  }
}
//---------------------
void OrderForm::printFile() {}
