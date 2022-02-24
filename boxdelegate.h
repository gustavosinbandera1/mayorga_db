#ifndef BOXDELEGATE_H
#define BOXDELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QWidget>

class boxDelegate : public QItemDelegate {
  Q_OBJECT
 public:
  explicit boxDelegate(QObject *parent = nullptr);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const override;
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const;
 signals:
};

#endif  // BOXDELEGATE_H
