#include "comboBoxDelegate.h"

#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QItemDelegate(parent) {}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
  QComboBox *editor = new QComboBox(parent);
  editor->addItem(QString("one in row %1").arg(index.row() + 1));
  editor->addItem(QString("two in row %1").arg(index.row() + 1));
  editor->addItem(QString("three in row %1").arg(index.row() + 1));
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
