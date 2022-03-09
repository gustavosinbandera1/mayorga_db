#include "lineeditordelegate.h"

#include <QComboBox>
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>

LineEditorDelegate::LineEditorDelegate(QObject *parent)
    : QItemDelegate(parent) {}

QWidget *LineEditorDelegate::createEditor(QWidget *parent,
                                          const QStyleOptionViewItem &option,
                                          const QModelIndex &index) const {
  qDebug() << "Delegator init**********************";
  QLineEdit *editor = new QLineEdit(parent);
  return editor;
}

void LineEditorDelegate::setEditorData(QWidget *editor,
                                       const QModelIndex &index) const {
  QString str = index.model()->data(index, Qt::DisplayRole).toString();
  qInfo() << "set editor  Data is " << str;

  QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
  lineEdit->setText(str);

  QString value = index.model()->data(index, Qt::EditRole).toString();
  lineEdit->setText(str);
}

void LineEditorDelegate::setModelData(QWidget *editor,
                                      QAbstractItemModel *model,
                                      const QModelIndex &index) const {
  QMessageBox::StandardButton reply;
  reply =
      QMessageBox::question(editor, "Save", "Do you want to save your changes?",
                            QMessageBox::Save | QMessageBox::Discard);

  if (reply == QMessageBox::Save) {
    qDebug()
        << "Yes was clicked setting model data from delegator................";
    QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
    QString str = lineEdit->text();
    qDebug() << "Setting data to model ";
    model->setData(index, str, Qt::EditRole);
  } else if (reply == QMessageBox::Discard)
    qDebug() << "Discard was clicked................";
}

void LineEditorDelegate::updateEditorGeometry(
    QWidget *editor, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  editor->setGeometry(option.rect);
}
