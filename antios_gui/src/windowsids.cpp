﻿#include <antios_gui/windowsids.h>

WindowsIDS::WindowsIDS(QWindow *parent)
    : QQuickView                        (parent)
#if 0
    , system_name_cbox_model_           (new ComboboxModel(this))
    , service_update_cbox_model_        (new ComboboxModel(this))
    , edition_cbox_model_               (new ComboboxModel(this))
    , product_type_cbox_model_          (new ComboboxModel(this))
    , build_number_cbox_model_          (new ComboboxModel(this))
#endif
    , is_system_name_cbox_active_       (true )
    , is_service_update_cbox_active_    (false)
    , is_edition_cbox_active_           (false)
    , is_product_type_cbox_active_      (true )
    , is_build_number_cbox_active_      (false)
    , is_product_id_line_active_        (false)
    , is_install_date_active_           (false)
    , is_build_guid_active_             (true )
{
    // TODO: fill data
#if 0
    QObject::connect(system_name_cbox_model_.get(),     &ComboboxModel::sigCurrentItemChanged, this, &WindowsIDS::sigItemChanged);
    QObject::connect(service_update_cbox_model_.get(),  &ComboboxModel::sigCurrentItemChanged, this, &WindowsIDS::sigItemChanged);
    QObject::connect(edition_cbox_model_.get(),         &ComboboxModel::sigCurrentItemChanged, this, &WindowsIDS::sigItemChanged);
    QObject::connect(product_type_cbox_model_.get(),    &ComboboxModel::sigCurrentItemChanged, this, &WindowsIDS::sigItemChanged);
    QObject::connect(build_number_cbox_model_.get(),    &ComboboxModel::sigCurrentItemChanged, this, &WindowsIDS::sigItemChanged);

    QObject::connect(system_name_cbox_model_.get(),     &ComboboxModel::sigCurrentIndexChanged, this, &WindowsIDS::onSystemNameIndexChanged);
    QObject::connect(service_update_cbox_model_.get(),  &ComboboxModel::sigCurrentIndexChanged, this, &WindowsIDS::onUpdateIndexChanged);
    QObject::connect(edition_cbox_model_.get(),         &ComboboxModel::sigCurrentIndexChanged, this, &WindowsIDS::onEditionIndexChanged);
    QObject::connect(product_type_cbox_model_.get(),    &ComboboxModel::sigCurrentIndexChanged, this, &WindowsIDS::onProductTypeIndexChanged);
    QObject::connect(build_number_cbox_model_.get(),    &ComboboxModel::sigCurrentIndexChanged, this, &WindowsIDS::onBuildNumberIndexChanged);
#endif
}

void WindowsIDS::setContextProperty(const QString &name, QObject *value)
{
    if (!name.isEmpty() && value != nullptr) {
        this->rootContext()->setContextProperty(name, value);
    }
}

void WindowsIDS::setIsSystemNameBoxActive(const bool value)
{
    is_system_name_cbox_active_ = value;
    emit sigSystemNameActiveChanged(is_system_name_cbox_active_);
}

void WindowsIDS::setIsServiceUpdateBoxActive(const bool value)
{
    is_service_update_cbox_active_ = value;
    emit sigServiceUpdateActiveChanged(is_service_update_cbox_active_);
}

void WindowsIDS::setIsEditionBoxActive(const bool value)
{
    is_edition_cbox_active_ = value;
    emit sigEditionActiveChanged(is_edition_cbox_active_);
}

void WindowsIDS::setIsProductTypeBoxActive(const bool value)
{
    is_product_type_cbox_active_ = value;
    emit sigProductTypeActiveChanged(is_product_type_cbox_active_);
}

void WindowsIDS::setIsBuildNumberBoxActive(const bool value)
{
    is_build_number_cbox_active_ = value;
    emit sigBuildNumberBoxActiveChanged(is_build_number_cbox_active_);
}

void WindowsIDS::setIsProductIdLineActive(const bool value)
{
    is_product_id_line_active_ = value;
    emit sigProductIdLineActiveChanged(is_product_id_line_active_);
}

void WindowsIDS::setIsInstallDateLineActive(const bool value)
{
    is_install_date_active_ = value;
    emit sigInstallDateLineActiveChanged(is_install_date_active_);
}

void WindowsIDS::setIsBuildGuidLineActive(const bool value)
{
    is_build_guid_active_ = value;
    emit sigBuildGuidLineActiveChanged(is_build_guid_active_);
}

const QString & WindowsIDS::getPropductId1() const
{
    return prod_id_1_; 
}

const QString & WindowsIDS::getPropductId2() const
{
    return prod_id_2_; 
}

const QString & WindowsIDS::getPropductId3() const
{ 
    return prod_id_3_; 
}

const QString & WindowsIDS::getPropductId4() const
{
    return prod_id_4_; 
}

void WindowsIDS::setProductId1(const QString &id)
{
    prod_id_1_ = id;
    onProdIdChanged(QString());
}

void WindowsIDS::setProductId2(const QString &id)
{
    prod_id_2_ = id;
    onProdIdChanged(QString());
}

void WindowsIDS::setProductId3(const QString &id)
{
    prod_id_3_ = id;
    onProdIdChanged(QString());
}

void WindowsIDS::setProductId4(const QString &id)
{
    prod_id_4_ = id;
    onProdIdChanged(QString());
}

const QString &WindowsIDS::getBuildGuid1() const
{
    return build_guid_1_;
}

const QString &WindowsIDS::getBuildGuid2() const
{
    return build_guid_2_;
}

const QString &WindowsIDS::getBuildGuid3() const
{
    return build_guid_3_;
}

const QString &WindowsIDS::getBuildGuid4() const
{
    return build_guid_4_;
}

const QString &WindowsIDS::getBuildGuid5() const
{
    return build_guid_5_;
}

void WindowsIDS::setBuildGuid1(const QString &guid1)
{
    build_guid_1_ = guid1;
    onBuildGUIDChanged(QString());
}

void WindowsIDS::setBuildGuid2(const QString &guid2)
{
    build_guid_2_ = guid2;
    onBuildGUIDChanged(QString());
}

void WindowsIDS::setBuildGuid3(const QString &guid3)
{
    build_guid_3_ = guid3;
    onBuildGUIDChanged(QString());
}

void WindowsIDS::setBuildGuid4(const QString &guid4)
{
    build_guid_4_ = guid4;
    onBuildGUIDChanged(QString());
}

void WindowsIDS::setBuildGuid5(const QString &guid5)
{
    build_guid_5_ = guid5;
    onBuildGUIDChanged(QString());
}

QString WindowsIDS::getAllProductId()
{
    return QString("%1-%2-%3-%4")
            .arg(prod_id_1_)
            .arg(prod_id_2_)
            .arg(prod_id_3_)
            .arg(prod_id_4_);
}

QString WindowsIDS::getAllBuildGuid()
{
    return QString("%1-%2-%3-%4-%5")
            .arg(build_guid_1_)
            .arg(build_guid_2_)
            .arg(build_guid_3_)
            .arg(build_guid_4_)
            .arg(build_guid_5_);
}

const QString &WindowsIDS::getInstallDate() const
{
    return install_date_;
}

void WindowsIDS::setInstallDate(const QString &date)
{
    if (!date.isEmpty()) {
        install_date_ = date;
        emit sigItemChanged(Item("win_install_date", "Installation Date", install_date_, ""));
    }
}

void WindowsIDS::onProdIdChanged(const QString &)
{
    emit sigItemChanged(Item("win_prod_id", "Product ID", getAllProductId(), ""));
}

void WindowsIDS::onBuildGUIDChanged(const QString &)
{
    emit sigItemChanged(Item("win_build_guid", "Build GUID", getAllBuildGuid(), ""));
}

void WindowsIDS::onSystemNameIndexChanged(const int index)
{
#if 0
    if (system_name_cbox_model_->getDefaultIndex() != index) {
        setIsServiceUpdateBoxActive(true);
        setIsEditionBoxActive(true);
        setIsProductTypeBoxActive(true);
    }
#endif
}

void WindowsIDS::onUpdateIndexChanged(const int index)
{
#if 0
    if (service_update_cbox_model_->getDefaultIndex() != index) {
        setIsInstallDateLineActive(true);
        setIsBuildNumberBoxActive(true);
    }
#endif
}

void WindowsIDS::onEditionIndexChanged(const int index)
{
#if 0
    if (edition_cbox_model_->getDefaultIndex() != index) {

    }
#endif
}

void WindowsIDS::onProductTypeIndexChanged(const int index)
{
#if 0
    if (product_type_cbox_model_->getDefaultIndex() != index) {
        setIsProductIdLineActive(true);
    }
#endif
}

void WindowsIDS::onBuildNumberIndexChanged(const int index)
{
}

