#include <mainwindow.h>

#include <QApplication>
#include <QFile>

#include "dbmanager.h"
#include "login.h"
#include "orderform.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setStyle("fusion");

  QString mainPath = QApplication::applicationDirPath();
  // set the app style sheet
  QString stylePath = mainPath + "/Medize.qss";
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

  // OrderForm form;
  // form.resize(640, 480);
  // form.createSample();
  // form.show();

  return a.exec();
}
