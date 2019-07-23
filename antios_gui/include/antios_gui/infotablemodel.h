#ifndef INFOTABLEMODEL_H
#define INFOTABLEMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QDebug>

#include <antios_gui/types.h>

class InfoTableModel : public QAbstractTableModel {
    Q_OBJECT
public:

    enum Roles {
        TitleRole = Qt::UserRole + 1,
        BeforeRole,
        AfterRole
    };

    explicit InfoTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows     (int row,    int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns  (int column, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override;

    void addItem(const Item& item);

    void clearAfter();

public slots:
    void onItemChanged(const Item& item);

private:
    QList<Item> data_;
};

//Q_DECLARE_METATYPE(InfoTableModel)
#endif // INFOTABLEMODEL_H
