
#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QDialog>
#include <QList>
#include <QPair>
#include <spinboxDelegate.h>
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTableWidget;
class QTextEdit;
class QWidget;
QT_END_NAMESPACE

class DetailsDialog : public QDialog
{
    Q_OBJECT

public:
    DetailsDialog(DbManager* dbm, const QString &title, QWidget *parent);

public slots:
    void verify();

public:
    QList<QPair<QString, int> > orderItems();
    QString senderName() const;
    QString senderAddress() const;
    bool sendOffers();

private:
    void setupItemsTable();

    QLabel *nameLabel;
    QLabel *addressLabel;
    QCheckBox *offersCheckBox;
    QLineEdit *nameEdit;
    QStringList items;
    QTableWidget *itemsTable;
    QTextEdit *addressEdit;
    QDialogButtonBox *buttonBox;

    void populateTable(int rows, int colums );
    //QTableWidget *pWidget;
    DbManager* _dbM;

    SpinboxDelegate *spinBoxDelegate;
};


#endif // DETAILSDIALOG_H
