#include "login.h"
//#include "dbmanager.h"
#include <QApplication>
#include <mainwindow.h>
#include "orderform.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyle("fusion");
//    DbManager db(HOST, USER, PWD, DBNAME);
//    Login login(&db);
//    if(login.exec() == QDialog::Rejected) {
//        return -1;
//    }
//    MainWindow mainWindow(&db, &login);

OrderForm form;
form.resize(640, 480);
form.show();

    return a.exec();
}
