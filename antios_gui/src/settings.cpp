#include "settings.h"

Settings::Settings(QWindow *parent)
    : QQuickView(parent)
    , url_                              (QString("qrc:/qml/Settings.qml"))
    , max_auto_saved_configurations_    (0)
    , number_of_unique_configurations_  (0)
    , start_with_os_                    (false)
    , display_all_ids_                  (false)
    , auto_export_configuration_        (false)
{
    setMaximumHeight(300);
    setMaximumWidth(400);

    setMinimumHeight(300);
    setMinimumWidth(400);

    this->rootContext()->setContextProperty("SettingsCPP", this);

    setModality     (Qt::WindowModal);
    setTitle        (QString("AntiOS Settings"));
    setSource       (url_);

    qDebug() << "Settings()";
}

Settings::~Settings() {
    qDebug() << "~Settings()";
}

int Settings::getMaxAutoSavedConfigurations() const {
    return max_auto_saved_configurations_;
}

int Settings::getNumberUniqueConfigurations() const {
    return number_of_unique_configurations_;
}

bool Settings::getStartWithOS() const {
    return start_with_os_;
}

bool Settings::getDisplayAllIds() const {
    return display_all_ids_;
}

bool Settings::getAutoExportConfiguration() const {
    return auto_export_configuration_;
}

void Settings::setMaxAutoSavedConfigurations(const int value) {
    max_auto_saved_configurations_ = value;
    emit sigMaxAutoConfigurationsChanged(max_auto_saved_configurations_);
}

void Settings::setNumbverUniqueConfigurations(const int value) {
    number_of_unique_configurations_ = value;
    emit sigNumberUniqueConfigurationsChanged(number_of_unique_configurations_);
}

void Settings::setStartWithOS(const bool value) {
    start_with_os_ = value;
    emit sigStartWithOSChanged(start_with_os_);
}

void Settings::setDisplayAllIds(const bool value) {
    display_all_ids_ = value;
    emit sigDisplayAllIds(display_all_ids_);
}

void Settings::setAutoExportConfiguration(const bool value) {
    auto_export_configuration_ = value;
    emit sigAutoExportConfigurationChanged(auto_export_configuration_);
}

void Settings::okButtonClicked() {
    qDebug() << "Ok Button clicked!";
    this->hide();
}

void Settings::save()
{

}

void Settings::load()
{

}

void Settings::importSettings()
{

}

void Settings::exportSettings()
{

}
