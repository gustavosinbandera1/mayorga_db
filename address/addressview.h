#ifndef ADDRESSVIEW_H
#define ADDRESSVIEW_H
#include <QWidget>

#include "dbmanager.h"
#include "readWriteModel.h"

class QueryModel;
class LineEditorDelegate;

namespace Ui {
class AddressView;
}

class AddressView : public QWidget {
  Q_OBJECT

 public:
  explicit AddressView(DbManager *mdb, QWidget *parent = nullptr);
  ~AddressView();
  void updateModel();

 private slots:
  void on_addressTableView_clicked(const QModelIndex &index);
  void on_streetNumberTextEdit_textChanged();
  void on_streetNumberTextEdit_copyAvailable(bool b);
  void on_streetNumberTextEdit_undoAvailable(bool b);

  void on_addressTableView_doubleClicked(const QModelIndex &index);

  void on_deleteButton_clicked();

private:
  Ui::AddressView *ui;
  QueryModel *addressModel;
  LineEditorDelegate *lineDelegate;
  DbManager* _dbM;
  void sendQuery();
};

#endif  // ADDRESSVIEW_H
