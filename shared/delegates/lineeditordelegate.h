#ifndef LINEEDITORDELEGATE_H
#define LINEEDITORDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QWidget>

class LineEditorDelegate : public QItemDelegate {
  Q_OBJECT
 public:
  explicit LineEditorDelegate(QObject *parent = nullptr);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;
 signals:
};

#endif  // LINEEDITORDELEGATE_H
