#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QtQuickControls2>

#include "application.h"
#include "ui/mainwindow.h"

int main (int argc, char *argv[]) {

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<InfoTableModel> ("InfoTableModel", 1, 0, "InfoTableModel");
    qmlRegisterType<Application>    ("Application", 1, 0, "Application");
    qmlRegisterType<MainWindow>     ("MainWindow", 1, 0, "MainWindow");
    qmlRegisterType<Settings>     ("SettingsCPP", 1, 0, "SettingsCPP");

    Application application;

    return app.exec();
}
