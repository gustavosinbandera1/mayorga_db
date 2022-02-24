#include "boxdelegate.h"

#include <QComboBox>

boxDelegate::boxDelegate(QObject *parent) : QItemDelegate(parent)
{

}

QWidget *boxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *editor = new QComboBox(parent);
    editor->addItem(QString("one in row %1").arg(index.row()+1));
    editor->addItem(QString("two in row %1").arg(index.row()+1));
    editor->addItem(QString("three in row %1").arg(index.row()+1));
     editor->addItem("Faber");
    return editor;
}

void boxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();

        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        //comboBox->setCurrentIndex(comboBox->findText(index.data().toString()));

        QString value = index.model()->data(index, Qt::DisplayRole).toString();
         comboBox->setCurrentIndex(comboBox->findText(value));
}

void boxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    //comboBox->interpretText();//is this important for the QComboBox delegate??
    QString str  = comboBox->currentText();

    model->setData(index, str, Qt::EditRole);
}

void boxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
editor->setGeometry(option.rect);
}
