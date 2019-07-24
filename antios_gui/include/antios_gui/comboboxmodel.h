#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <antios_gui/types.h>

#include <QAbstractListModel>
#include <QDebug>

class ComboboxModel : public QAbstractListModel 
{
    Q_OBJECT
public:
    Q_PROPERTY(int default_index READ getDefaultIndex)

    explicit ComboboxModel(QObject *parent = nullptr, const int default_index = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addItem(const Item& item);

    void addItems(const QVector<Item>& items);

    void addItems(const QList<Item>& items);

    QList<Item>& getData();

    Q_INVOKABLE void currentIndexChanged(const int index);

    Q_INVOKABLE int getDefaultIndex() const;

signals:

    void sigCurrentItemChanged(const Item& item);

    void sigCurrentIndexChanged(const int index);

private:
    QList<Item> data_;
    const int default_index_;
};

#endif // COMBOBOXMODEL_H
