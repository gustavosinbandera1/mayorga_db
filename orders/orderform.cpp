#include "orderform.h"

#include <QDate>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextFrame>
#include <QTextTable>

#include "dbmanager.h"
#include "login.h"
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
void OrderForm::createLetter(QString &&name, QString &&address,
                             QList<DTODetails> &&orderItems) {
  QTextEdit *editor = new QTextEdit;
  int tabIndex = lettersTab->addTab(editor, name);
  lettersTab->setCurrentIndex(tabIndex);

  QTextCursor cursor(editor->textCursor());
  cursor.movePosition(QTextCursor::Start);

  QTextFrame *topFrame = cursor.currentFrame();

  QTextFrameFormat topFrameFormat = topFrame->frameFormat();
  topFrameFormat.setPadding(8);
  topFrame->setFrameFormat(topFrameFormat);

  QTextCharFormat textFormat;
  QTextCharFormat boldFormat;
  boldFormat.setFontWeight(QFont::Bold);

  //-----------------------------------------------------------------------------------
  QTextFrameFormat addressFrameFormat;
  addressFrameFormat.setBorder(3);
  addressFrameFormat.setPosition(QTextFrameFormat::FloatRight);
  addressFrameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 40));

  cursor.insertFrame(addressFrameFormat);

  cursor.insertText("A company", boldFormat);
  cursor.insertBlock();
  cursor.insertText("Extra Test Information ");
  cursor.insertBlock();
  cursor.insertText("Industry Park");
  cursor.insertBlock();
  cursor.insertText("Another place");

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

  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------

  QTextFrameFormat bodyFrameFormat;
  bodyFrameFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
  cursor.insertFrame(bodyFrameFormat);

  cursor.insertText(tr("I would like to place an order for the following "
                       "items:"),
                    textFormat);
  cursor.insertBlock();
  cursor.insertBlock();

  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  QTextTableFormat orderTableFormat;
  orderTableFormat.setAlignment(Qt::AlignHCenter);
  QTextTable *orderTable = cursor.insertTable(1, 4, orderTableFormat);

  //----------------------------------------------------------------------------
  QTextFrameFormat orderFrameFormat = cursor.currentFrame()->frameFormat();
  orderFrameFormat.setBorder(1);
  cursor.currentFrame()->setFrameFormat(orderFrameFormat);

  cursor = orderTable->cellAt(0, 0).firstCursorPosition();
  cursor.insertText(tr("Product"), boldFormat);
  cursor = orderTable->cellAt(0, 1).firstCursorPosition();
  cursor.insertText(tr("Quantity"), boldFormat);

  cursor = orderTable->cellAt(0, 2).firstCursorPosition();
  cursor.insertText(tr("Price"), boldFormat);

  cursor = orderTable->cellAt(0, 3).firstCursorPosition();
  cursor.insertText(tr("Total"), boldFormat);

  for (int i = 0; i < orderItems.count(); ++i) {
    DTODetails item = orderItems[i];
    int row = orderTable->rows();

    orderTable->insertRows(row, 1);
    cursor = orderTable->cellAt(row, 0).firstCursorPosition();
    cursor.insertText(item.productName, textFormat);

    cursor = orderTable->cellAt(row, 1).firstCursorPosition();
    cursor.insertText(QString("%1").arg(item.quantity), textFormat);

    cursor = orderTable->cellAt(row, 2).firstCursorPosition();
    cursor.insertText(QString("%1").arg(item.price), textFormat);

    cursor = orderTable->cellAt(row, 3).firstCursorPosition();
    cursor.insertText(QString("%1").arg(item.purchase), textFormat);
  }

  cursor.setPosition(topFrame->lastPosition());

  cursor.insertBlock();

  cursor.insertText(
      tr("Please update my records to take account of the "
         "following privacy information:"));
  cursor.insertBlock();

  cursor.setPosition(topFrame->lastPosition());
  cursor.insertBlock();
  cursor.insertText(tr("Sincerely,"), textFormat);
  cursor.insertBlock();
  cursor.insertBlock();
  cursor.insertBlock();
  cursor.insertText(name);

  editor->setReadOnly(true);
  printAction->setEnabled(true);
}
//---------------------
void OrderForm::createSample() {
  DetailsDialog dialog(_dbM, "Dialog with default values", this);
  createLetter("Mr. Smith", "12 High Street\nSmall Town\nThis country",
               dialog.orderItems());
}
//---------------------
OrderForm::~OrderForm() { qDebug() << "deleting Order Form"; }
//---------------------
void OrderForm::openDialog() {
  DetailsDialog dialog(_dbM, tr("Enter customer Details"), this);
  if (dialog.exec() == QDialog::Accepted) {
    createLetter(dialog.getSenderName(), dialog.getSenderAddress(),
                 dialog.orderItems());


    if(!dialog.isEmpty)
        saveOrder(dialog.orderItems(), dialog.getPaymenMethod());
  }
}
//------------------------
bool OrderForm::saveOrder(QList<DTODetails> orderItems, QString paymentMethod) {

  QSqlQuery q(_dbM->db());
  QDateTime dateTime = QDateTime::currentDateTime();
  QString payment = paymentMethod;

  q.prepare(
      "INSERT INTO orders (fk_customer_id, created_date_time, payment_type) "
      "VALUES ( :customer_id, :dateTime, :payment)");
  q.bindValue(":customer_id", UserData::userId);
  q.bindValue(":dateTime", dateTime);
  q.bindValue(":payment", payment);

  if (!q.exec()) {
    qDebug() << "**************ERROR************";
    // handle error
  }
  int lastInsertedId = q.lastInsertId().toInt();
  qDebug() << "Last inserted ID: " << lastInsertedId;

  return true;
}
//---------------------
void OrderForm::printFile() {}
