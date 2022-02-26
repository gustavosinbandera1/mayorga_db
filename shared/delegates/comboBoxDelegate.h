#ifndef BOXDELEGATE_H
#define BOXDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QWidget>
#include "dbmanager.h"

class ComboBoxDelegate : public QItemDelegate {
  Q_OBJECT
 public:
  explicit ComboBoxDelegate(DbManager* dbm,QString table, QString column, QObject *parent);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;
 signals:

private:
  DbManager* _dbM;
  QString _table;
  QString _column;
  QStringList boxItems;
};

#endif  // BOXDELEGATE_H
