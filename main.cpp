#include <mainwindow.h>
#include <qsqlconnectiondialog.h>

#include <QApplication>
#include <QFile>
#include <QtWidgets>

#include "browser.h"
#include "dbmanager.h"
#include "login.h"
#include "orderform.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  // a.setStyle("fusion");

  QString mainPath = QApplication::applicationDirPath();
  // set the app style sheet
  QString stylePath = mainPath + "/sql/Medize.qss";
  QFile styleSheetFile(stylePath);
  styleSheetFile.open(QFile::QIODevice::ReadOnly);
  QString styleSheet = styleSheetFile.readAll();

  DbManager db(HOST, USER, PWD, DBNAME);

  Login login(&db);

  login.setStyleSheet(styleSheet);

  login.setWindowTitle(QObject::tr("MayorgaDB Login"));
  if (login.exec() == QDialog::Rejected) {
    return -1;
  }

  MainWindow mainWindow(&db, &login);
  mainWindow.show();

  /////////////////////////////////////
  //////////////////////////////////////////

  QMainWindow mainWin(&mainWindow);
  mainWin.setWindowTitle(QObject::tr("Qt SQL Browser"));

  Browser browser(&mainWin);
  mainWin.setCentralWidget(&browser);

  QMenu *fileMenu = mainWin.menuBar()->addMenu(QObject::tr("&File"));
  fileMenu->addAction(QObject::tr("Add &Connection..."),
                      [&]() { browser.addConnection(); });
  fileMenu->addSeparator();
  fileMenu->addAction(QObject::tr("&Quit"), []() { qApp->quit(); });

  QMenu *helpMenu = mainWin.menuBar()->addMenu(QObject::tr("&Help"));
  helpMenu->addAction(QObject::tr("About"), [&]() { browser.about(); });
  helpMenu->addAction(QObject::tr("About Qt"), []() { qApp->aboutQt(); });

  QObject::connect(&browser, &Browser::statusMessage,
                   [&mainWin](const QString &text) {
                     mainWin.statusBar()->showMessage(text);
                   });

  mainWin.show();
  browser.refreshConnection();

  if (QSqlDatabase::connectionNames().isEmpty())
    QMetaObject::invokeMethod(&browser, "addConnection", Qt::QueuedConnection);

  ///////////////////////////
  //   OrderForm form;
  //   form.resize(640, 480);
  //   form.createSample();
  //   form.show();

  return a.exec();
}
