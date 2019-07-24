#include <antios_gui/mainwindow.h>

MainWindow::MainWindow(QWindow *parent)
    : QQuickView            (parent)
    , url_                  (QStringLiteral("qrc:/qml/main.qml"))
    , ids_tab_              (new WindowsIDS(this))
    , settings_             (new Settings())
    , table_model_          (new InfoTableModel(this))
    , is_buttons_active_    (true)
{
    table_model_->addItem(Item("win_ver",            "Windows Version",        "Windows 7",                             ""));
    table_model_->addItem(Item("win_edition",        "Windows Edition",        "Professional",                          ""));
    table_model_->addItem(Item("win_build",          "Windows Build",          "6.1.7600",                              ""));
    table_model_->addItem(Item("win_install_date",   "Installation Date",      "01.01.2020",                            ""));
    table_model_->addItem(Item("win_user_name",      "User Name",              "Helmut",                                ""));
    table_model_->addItem(Item("win_pc_name",        "Computer Name",          "User-PC",                               ""));
    table_model_->addItem(Item("win_mac",            "MAC Address",            "AA-BB-CC-11-22-33",                     ""));
    table_model_->addItem(Item("win_vol_id",         "Volume ID",              "1A2B-3C4D",                             ""));
    table_model_->addItem(Item("win_prod_id",        "Product ID",             "14356-436-3443546-45554",               ""));
    table_model_->addItem(Item("win_build_guid",     "Build GUID",             "22345200-abe8-4f60-90c8-0d43c5f6c0f6",  ""));
    table_model_->addItem(Item("win_prod_type",      "Product Type",           "Retail",                                ""));
    table_model_->addItem(Item("win_update",         "Service Pack/Update",    "SP1",                                   ""));

    table_model_->setHeaderData(0, Qt::Horizontal, QVariant("Identifier"), Qt::DisplayRole);
    table_model_->setHeaderData(1, Qt::Horizontal, QVariant("Before"    ), Qt::DisplayRole);
    table_model_->setHeaderData(2, Qt::Horizontal, QVariant("After"     ), Qt::DisplayRole);

    this->setContextProperty("MainWindow",          this);
    this->setContextProperty("WindowsIDS",          ids_tab_.get());
    this->setContextProperty("InfoTableModel",      table_model_.get());
    this->setContextProperty("SystemNameModel",     ids_tab_->getSystemNameModel().get());
    this->setContextProperty("ServiceUpdateModel",  ids_tab_->getServiceUpdateModel().get());
    this->setContextProperty("EditionModel",        ids_tab_->getEditionModel().get());
    this->setContextProperty("ProductTypeModel",    ids_tab_->getProductTypeNameModel().get());
    this->setContextProperty("BuildNumberModel",    ids_tab_->getBuildNumberModel().get());

    QObject::connect(ids_tab_.get(), &WindowsIDS::sigItemChanged, table_model_.get(), &InfoTableModel::onItemChanged);

    setSource(url_);
}

void MainWindow::setContextProperty(const QString &name, QObject *value) 
{
    this->rootContext()->setContextProperty(name, value);
}

bool MainWindow::getButtonsIsActive() const 
{
    return is_buttons_active_;
}

Q_INVOKABLE void MainWindow::setButtonsIsActive(bool value) 
{
    is_buttons_active_ = value;
    emit sigButtonsActiveChanged(is_buttons_active_);
}

void MainWindow::onApplyCLicked() 
{
    qDebug() << "onApplyCLicked() invoked!";
}

void MainWindow::onRandomizeCLicked() {
    qDebug() << "onApplyCLicked() invoked!";
}

void MainWindow::exportConfiguration()
{
    qDebug() << "Export Configuration";
}

void MainWindow::importConfiguration()
{
    qDebug() << "Import Configuration";
}

void MainWindow::backToInitialConfiguration()
{
    qDebug() << "Back to Initial Configuration";
}

void MainWindow::quitConfiguration()
{
    qDebug() << "Quit from app";
    QCoreApplication::exit(0);
}

void MainWindow::configurationRandomizeAll() 
{
    qDebug() << "Configuration Randomize All";
}

void MainWindow::configurationRandomizeWindowsIDs() 
{
    qDebug() << "Configuration Randomize WindowsIDS";
}

void MainWindow::configurationRandomizeWebRTC() 
{
    qDebug() << "Configuration Randomize WebRTC";
}

void MainWindow::configurationRandomizeTelemetry() 
{
    qDebug() << "Configuration Randomize Telemetry";
}

void MainWindow::configurationRandomizeBrowser() 
{
    qDebug() << "Configuration Randomize Browser";
}

void MainWindow::configurationRandomizeHardware() 
{
    qDebug() << "Configuration Randomize Hardware";
}

void MainWindow::optionsApplicationSettings()
{
    qDebug() << "Application Settings";
}

void MainWindow::optionsImportSettings()
{
    qDebug() << "Import Settings";
    settings_->importSettings();
}

void MainWindow::optionsExportSettings()
{
    qDebug() << "Export Settings";
    settings_->exportSettings();
}

void MainWindow::helpTechnicalHelp()
{
    qDebug() << "Technical Help";
}

void MainWindow::helpEmailToSupport()
{
    qDebug() << "Email to supprort";
}

void MainWindow::helpCheckToUpdates()
{
    qDebug() << "check to updates";
}

void MainWindow::helpAbout()
{
    qDebug() << "About";
}

bool MainWindow::isTelemetryActive() const 
{
    return (QSysInfo::productVersion() == QString("10"));
}

void MainWindow::showSettings()
{
    qDebug() << "Try to show SettingsForm";
    settings_->show();
}

void MainWindow::clearAfter() 
{
    table_model_->clearAfter();
}
