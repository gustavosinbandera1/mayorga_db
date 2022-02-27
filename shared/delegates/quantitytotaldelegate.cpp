#include "quantitytotaldelegate.h"
#include <QDebug>


QuantityTotalDelegate::QuantityTotalDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}


QWidget *QuantityTotalDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
  qDebug() << "Creating editor .....";
  QSpinBox *editor = new QSpinBox(parent);
  editor->setMinimum(0);
  editor->setMaximum(1000000);
  return editor;
}

void QuantityTotalDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const {
  qDebug() << "Editing Data:  ";
  int value = index.model()->data(index, Qt::EditRole).toInt();
  QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
  spinBox->setValue(value);
}

void QuantityTotalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const {
  qDebug() << "Setting Model data";
  QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
  spinBox->interpretText();
  int value = spinBox->value();
  model->setData(index, value, Qt::EditRole);
}

void QuantityTotalDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
  editor->setGeometry(option.rect);
  qDebug() << "updating geometry ................";
}
