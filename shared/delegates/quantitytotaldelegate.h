#ifndef QUANTITYTOTALDELEGATOR_H
#define QUANTITYTOTALDELEGATOR_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QSpinBox>

class QuantityTotalDelegate : public QItemDelegate {
  Q_OBJECT

 public:
  explicit QuantityTotalDelegate(QObject *parent = nullptr);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;
 signals:
};

#endif  // QUANTITYTOTALDELEGATOR_H
