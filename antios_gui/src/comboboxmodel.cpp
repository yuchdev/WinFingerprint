#include <antios_gui/comboboxmodel.h>

ComboboxModel::ComboboxModel(QObject *parent, const int default_index)
    : QAbstractListModel(parent)
    , default_index_    (default_index)
{
}

int ComboboxModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return data_.size();
}

QVariant ComboboxModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > data_.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return QVariant(data_[index.row()].before_);
    else
        return QVariant();

}

void ComboboxModel::addItem(const Item &item)
{
    beginInsertRows(QModelIndex(), data_.size(), data_.size());
    data_.push_back(item);
    endInsertRows();
    QModelIndex index = createIndex(data_.size(), 0, static_cast<void *>(nullptr));
    emit dataChanged(index, index);

}

void ComboboxModel::addItems(const QVector<Item> &items)
{
    for (auto& it: items) addItem(it);
}

void ComboboxModel::addItems(const QList<Item> &items)
{
    data_ = items;
}

QList<Item> &ComboboxModel::getData()
{
    return data_;
}

void ComboboxModel::currentIndexChanged(const int index)
{
    if (index > data_.size() || index < 0)
        return;

    qDebug() << "Index changed to: " << index;
    emit sigCurrentItemChanged(data_[index]);
    emit sigCurrentIndexChanged(index);
}

int ComboboxModel::getDefaultIndex() const
{
    return default_index_;
}
