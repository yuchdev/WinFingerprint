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

    Q_PROPERTY(QString install_date READ getInstallDate WRITE setInstallDate)

    explicit WindowsIDS(QWindow *parent = nullptr);
    void setContextProperty(const QString& name, QObject* value);

    Q_INVOKABLE void setInstallDate (const QString& date);

    QStringListModel& productNameModel() { return _productNameModel; };
    QStringListModel& subproductNameModel() { return _subproductNameModel; };
    QStringListModel& productTypeModel() { return _productTypeModel; };
    QStringListModel& editionModel() { return _editionModel; };
    QStringListModel& buildNumberModel() { return _buildNumberModel; };

private:

    QString getAllProductId();
    QString getAllBuildGuid();

    const QString &getInstallDate() const;

signals:
    void sigItemChanged(const Item& item);


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

    /// @brief
    void loadSubproducts(const QString& product);

    /// @brief
    void loadEditions(const QString& product);

    /// @brief
    void loadBuilds(const QString& subproduct);


private:

    /// @brief
    void initialLoad();



private:

    QStringListModel _productNameModel;
    QStringListModel _subproductNameModel;
    QStringListModel _productTypeModel;
    QStringListModel _editionModel;
    QStringListModel _buildNumberModel;

    //////////////////////////////////////////////////////////////////////////

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
