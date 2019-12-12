#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QObject>
#include <QVariant>
#include <QSysInfo>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlComponent>
#include <QCoreApplication>

#include "settings.h"
#include "windowsids.h"
#include "../models/comboboxmodel.h"
#include "../models/infotablemodel.h"

class MainWindow : public QQuickView {
    Q_OBJECT
public:

    Q_PROPERTY(bool buttons_active READ getButtonsIsActive WRITE setButtonsIsActive NOTIFY sigButtonsActiveChanged)
    Q_PROPERTY(bool telemetry_active READ isTelemetryActive)

    explicit MainWindow         (QWindow *parent = nullptr);
    void setContextProperty     (const QString& name, QObject* value);

    Q_INVOKABLE bool getButtonsIsActive() const;
    Q_INVOKABLE void setButtonsIsActive(const bool value);

    Q_INVOKABLE void onApplyCLicked();
    Q_INVOKABLE void onRandomizeCLicked();

    //// Configuration menu callbacks
    Q_INVOKABLE void exportConfiguration();
    Q_INVOKABLE void importConfiguration();
    Q_INVOKABLE void backToInitialConfiguration();
    Q_INVOKABLE void quitConfiguration();

    //// Configuration menu Randomize submenu callbacks
    Q_INVOKABLE void configurationRandomizeAll();
    Q_INVOKABLE void configurationRandomizeWindowsIDs();
    Q_INVOKABLE void configurationRandomizeWebRTC();
    Q_INVOKABLE void configurationRandomizeTelemetry();
    Q_INVOKABLE void configurationRandomizeBrowser();
    Q_INVOKABLE void configurationRandomizeHardware();

    /// Options menu callbacks
    Q_INVOKABLE void optionsApplicationSettings();
    Q_INVOKABLE void optionsImportSettings();
    Q_INVOKABLE void optionsExportSettings();

    /// Help menu callbacks
    Q_INVOKABLE void helpTechnicalHelp();
    Q_INVOKABLE void helpEmailToSupport();
    Q_INVOKABLE void helpCheckToUpdates();
    Q_INVOKABLE void helpAbout();

    Q_INVOKABLE bool isTelemetryActive() const;

    Q_INVOKABLE void showSettings();
signals:
    void sigButtonsActiveChanged(const bool value);

public slots:

private:
    void clearAfter();
private:
    QUrl url_;

    QSharedPointer<WindowsIDS>      ids_tab_;
    QSharedPointer<Settings>        settings_;

    QSharedPointer<InfoTableModel>  table_model_;

    bool is_buttons_active_;
};

#endif // MAINWINDOW_H
