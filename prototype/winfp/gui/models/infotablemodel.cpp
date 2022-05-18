#include "infotablemodel.h"

InfoTableModel::InfoTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{ }

QVariant InfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    /// FIXME: Implement me!
    return QVariant();
}

bool InfoTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) {
    if (value != headerData(section, orientation, role)) {
        /// FIXME: Implement me!
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}


int InfoTableModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return data_.size();
}

int InfoTableModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3;
}

QVariant InfoTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() > data_.size()) {
        return QVariant();
    }

    switch (role) {
    case Roles::TitleRole:
        return QVariant(data_[index.row()].title_);
    case Roles::BeforeRole:
        return QVariant(data_[index.row()].before_);
    case Roles::AfterRole:
        return QVariant(data_[index.row()].after_);
    default:
        return QVariant();
    }

}

bool InfoTableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (data(index, role) != value) {
        /// emit dataChanged(index, index, QVector<int>() << role);
        return false;
    }
    return false;
}

Qt::ItemFlags InfoTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool InfoTableModel::insertRows(int row, int count, const QModelIndex &parent) {
    beginInsertRows(parent, row, row + count - 1);
    /// FIXME: Implement me!
    endInsertRows();
    return false;
}

bool InfoTableModel::insertColumns(int column, int count, const QModelIndex &parent) {
    beginInsertColumns(parent, column, column + count - 1);
    endInsertColumns();
    return false;
}

bool InfoTableModel::removeRows(int row, int count, const QModelIndex &parent) {
    beginRemoveRows(parent, row, row + count - 1);
    endRemoveRows();
    return false;
}

bool InfoTableModel::removeColumns(int column, int count, const QModelIndex &parent) {
    beginRemoveColumns(parent, column, column + count - 1);
    endRemoveColumns();
    return false;
}

QHash<int, QByteArray> InfoTableModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Roles::TitleRole]     = "title";
    roles[Roles::BeforeRole]    = "before";
    roles[Roles::AfterRole]     = "after";
    return roles;
}

void InfoTableModel::addItem(const Item &item) {
    beginInsertRows(QModelIndex(), data_.size(), data_.size());
    data_.push_back(item);
    endInsertRows();
    QModelIndex index = createIndex(data_.size(), 0, static_cast<void *>(nullptr));
    emit dataChanged(index, index);
}

void InfoTableModel::clearAfter() {
    for (int i(0); i < data_.size(); ++i) {
        data_[i].after_.clear();
        QModelIndex index = createIndex(i, 0, static_cast<void *>(nullptr));
        emit dataChanged(index, index);
    }
}

void InfoTableModel::onItemChanged(const Item &item) {
    for (int i(0); i < data_.size(); ++i) {
        if (data_[i].param_name_ == item.param_name_) {
            qDebug() << "[TABLE]: Change FROM: '" << data_[i].before_ << "' TO: '" << item.before_ << "'";
            data_[i].after_ = item.before_;
            QModelIndex index = createIndex(i, 0, static_cast<void *>(nullptr));
            emit dataChanged(index, index);
            break;
        }
    }
}

