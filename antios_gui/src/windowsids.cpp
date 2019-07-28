#include <antios_gui/windowsids.h>
#include <winfp/windows_fpdata.h>

#include <QQuickItem>
#include <QComboBox>
#include <QStringList>

using namespace antios;

WindowsIDS::WindowsIDS(QWindow *parent) : QQuickView(parent)
{
    initialLoad();
}

void WindowsIDS::initialLoad()
{
    // Windows 7/8/8.1/10
    QStringList productNamesList;
    productNamesList << "Windows 7" << "Windows 8" << "Windows 8.1" << "Windows 10";
    _productNameModel.setStringList(productNamesList);
    loadSubproducts(productNamesList[0]);
    loadEditions(productNamesList[0]);

    // Retail/OEM
    QStringList productTypesList;
    productTypesList << "Retail" << "OEM";
    _productTypeModel.setStringList(productTypesList);
}


void WindowsIDS::loadSubproducts(const QString& product)
{
    if (product.isEmpty())
        return;
    WindowsFingerprintData::ProductInfo prod = WindowsFingerprintData::get_product(product.toStdString());
    std::vector<WindowsFingerprintData::SubproductName> subproducts = WindowsFingerprintData::subproducts_by_product(prod.product_name_id);
    QStringList subproductNamesList;
    for (auto subproduct : subproducts) {
        WindowsFingerprintData::SubproductInfo subprod_info = WindowsFingerprintData::get_subproduct(subproduct);
        subproductNamesList.push_back(QString::fromStdString(subprod_info.subproduct_name));
    }
    _subproductNameModel.setStringList(subproductNamesList);
}


void WindowsIDS::loadEditions(const QString& product)
{
    if (product.isEmpty())
        return;
    WindowsFingerprintData::ProductInfo prod = WindowsFingerprintData::get_product(product.toStdString());
    auto editions = WindowsFingerprintData::editions_by_product(prod.product_name_id);

    QStringList editionsNamesList;
    for (auto edition : editions) {
        editionsNamesList.push_back(QString::fromStdString(edition.second.readable_name));
    }
    _editionModel.setStringList(editionsNamesList);

}

void WindowsIDS::setContextProperty(const QString &name, QObject *value)
{
    if (!name.isEmpty() && value != nullptr) {
        this->rootContext()->setContextProperty(name, value);
    }
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
