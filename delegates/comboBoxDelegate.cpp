#include "comboBoxDelegate.h"

#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(DbManager *dbm, QString table,
                                   QString column, QObject *parent)
    : QItemDelegate(parent) {
  _dbM = dbm;
  _table = table;
  _column = column;
  QSqlQuery query;
  QString c = QString("SELECT * FROM %1 ").arg(table);
  if (!query.exec(c)) {
    qDebug() << "--------------------error--------------------------";
  }
  while (query.next()) {
    qDebug() << "output: " << query.value(3);
    boxItems.append(query.value(3).toString());
  }
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
  qDebug() << "--------------------creating editor--------------------------";
  QComboBox *editor = new QComboBox(parent);;
  for (const auto &item : boxItems) {
    qDebug() << item;
    editor->addItem(item);
  }
  return editor;
}

void ComboBoxDelegate::setEditorData(QWidget *editor,
                                     const QModelIndex &index) const {
  QString str = index.model()->data(index, Qt::EditRole).toString();
  QComboBox *comboBox = static_cast<QComboBox *>(editor);
  // comboBox->setCurrentIndex(comboBox->findText(index.data().toString()));

  QString value = index.model()->data(index, Qt::DisplayRole).toString();
  comboBox->setCurrentIndex(comboBox->findText(value));
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const {
  QComboBox *comboBox = static_cast<QComboBox *>(editor);
  QString str = comboBox->currentText();
  model->setData(index, str, Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const {
  editor->setGeometry(option.rect);
}
