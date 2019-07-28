#pragma once

#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QVariant>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlComponent>

class Settings : public QQuickView
{
    Q_OBJECT
public:
    explicit Settings(QWindow *parent = nullptr);

    virtual ~Settings();

    Q_INVOKABLE int  getMaxAutoSavedConfigurations  () const;
    Q_INVOKABLE int  getNumberUniqueConfigurations  () const;
    Q_INVOKABLE bool getStartWithOS                 () const;
    Q_INVOKABLE bool getDisplayAllIds               () const;
    Q_INVOKABLE bool getAutoExportConfiguration     () const;

    Q_INVOKABLE void setMaxAutoSavedConfigurations  (const int  value);
    Q_INVOKABLE void setNumbverUniqueConfigurations (const int  value);
    Q_INVOKABLE void setStartWithOS                 (const bool value);
    Q_INVOKABLE void setDisplayAllIds               (const bool value);
    Q_INVOKABLE void setAutoExportConfiguration     (const bool value);

    Q_INVOKABLE void okButtonClicked();

    void save();
    void load();

    void importSettings();
    void exportSettings();

signals:
    void sigMaxAutoConfigurationsChanged        (const int  value);
    void sigNumberUniqueConfigurationsChanged   (const int  value);
    void sigStartWithOSChanged                  (const bool value);
    void sigDisplayAllIds                       (const bool value);
    void sigAutoExportConfigurationChanged      (const bool value);

private:
    QUrl url_;

    int max_auto_saved_configurations_;
    int number_of_unique_configurations_;
    bool start_with_os_;
    bool display_all_ids_;
    bool auto_export_configuration_;
};
