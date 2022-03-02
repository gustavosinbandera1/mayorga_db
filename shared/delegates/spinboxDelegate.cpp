#include "spinboxDelegate.h"
#include <QDebug>

SpinboxDelegate::SpinboxDelegate(QObject *parent) : QItemDelegate(parent) {}
//---------------------------------------
QWidget *SpinboxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
 if (index.column() != 0){
    qDebug() << "Creating editor .....";
  QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
  editor->setMinimum(0);
  editor->setMaximum(1000000);
  return editor;
 }
}
//---------------------------------------
void SpinboxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const {
        QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox *>(editor);
        spinBox->setValue(index.data().toDouble());
}
//---------------------------------------
void SpinboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const {
  qDebug() << "Setting Model data";
  QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox *>(editor);
  spinBox->interpretText();
  int value = spinBox->value();
  model->setData(index, value, Qt::EditRole);
}
//---------------------------------------
void SpinboxDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
  editor->setGeometry(option.rect);
  qDebug() << "updating geometry ................";
}
