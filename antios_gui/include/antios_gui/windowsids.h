#pragma once

#include <antios_gui/types.h>

#include <QDebug>
#include <QObject>
#include <QVariant>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlComponent>
#include <QStringListModel>


class WindowsIDS : public QQuickView 
{
    Q_OBJECT

public:
    Q_PROPERTY(QString product_id_1 READ getPropductId1 WRITE setProductId1 NOTIFY sigChecngedProdID1)
    Q_PROPERTY(QString product_id_2 READ getPropductId2 WRITE setProductId2 NOTIFY sigChecngedProdID2)
    Q_PROPERTY(QString product_id_3 READ getPropductId3 WRITE setProductId3 NOTIFY sigChecngedProdID3)
    Q_PROPERTY(QString product_id_4 READ getPropductId4 WRITE setProductId4 NOTIFY sigChecngedProdID4)

    Q_PROPERTY(QString guid_1 READ getBuildGuid1 WRITE setBuildGuid1 NOTIFY sigChangedGuid1)
    Q_PROPERTY(QString guid_2 READ getBuildGuid2 WRITE setBuildGuid2 NOTIFY sigChangedGuid2)
    Q_PROPERTY(QString guid_3 READ getBuildGuid3 WRITE setBuildGuid3 NOTIFY sigChangedGuid3)
    Q_PROPERTY(QString guid_4 READ getBuildGuid4 WRITE setBuildGuid4 NOTIFY sigChangedGuid4)
    Q_PROPERTY(QString guid_5 READ getBuildGuid5 WRITE setBuildGuid5 NOTIFY sigChangedGuid5)

    Q_PROPERTY(QString install_date READ getInstallDate WRITE setInstallDate)

    explicit WindowsIDS(QWindow *parent = nullptr);
    void setContextProperty(const QString& name, QObject* value);

    Q_INVOKABLE void setInstallDate (const QString& date);

private:
    const QString &getPropductId1() const;
    const QString &getPropductId2() const;
    const QString &getPropductId3() const;
    const QString &getPropductId4() const;

    void setProductId1(const QString& id);
    void setProductId2(const QString& id);
    void setProductId3(const QString& id);
    void setProductId4(const QString& id);

    const QString& getBuildGuid1() const;
    const QString& getBuildGuid2() const;
    const QString& getBuildGuid3() const;
    const QString& getBuildGuid4() const;
    const QString& getBuildGuid5() const;

    void setBuildGuid1(const QString& guid1);
    void setBuildGuid2(const QString& guid2);
    void setBuildGuid3(const QString& guid3);
    void setBuildGuid4(const QString& guid4);
    void setBuildGuid5(const QString& guid5);

    QString getAllProductId();
    QString getAllBuildGuid();

    const QString &getInstallDate() const;

signals:
    void sigItemChanged(const Item& item);

    void sigChecngedProdID1(const QString& id);
    void sigChecngedProdID2(const QString& id);
    void sigChecngedProdID3(const QString& id);
    void sigChecngedProdID4(const QString& id);

    void sigChangedGuid1(const QString& guid);
    void sigChangedGuid2(const QString& guid);
    void sigChangedGuid3(const QString& guid);
    void sigChangedGuid4(const QString& guid);
    void sigChangedGuid5(const QString& guid);

    void sigSystemNameActiveChanged      (const bool value);
    void sigServiceUpdateActiveChanged   (const bool value);
    void sigEditionActiveChanged         (const bool value);
    void sigProductTypeActiveChanged     (const bool value);
    void sigBuildNumberBoxActiveChanged  (const bool value);
    void sigProductIdLineActiveChanged   (const bool value);
    void sigInstallDateLineActiveChanged (const bool value);
    void sigBuildGuidLineActiveChanged   (const bool value);

    void sigInstallDateChanged(const QString& date);

public slots:
    void onProdIdChanged(const QString&);
    void onBuildGUIDChanged(const QString&);

    void onSystemNameIndexChanged   (const int index);
    void onUpdateIndexChanged       (const int index);
    void onEditionIndexChanged      (const int index);
    void onProductTypeIndexChanged  (const int index);
    void onBuildNumberIndexChanged  (const int index);

private:

    QString prod_id_1_;
    QString prod_id_2_;
    QString prod_id_3_;
    QString prod_id_4_;

    QString install_date_;

    QString build_guid_1_;
    QString build_guid_2_;
    QString build_guid_3_;
    QString build_guid_4_;
    QString build_guid_5_;
};
