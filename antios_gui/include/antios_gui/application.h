#pragma once

#include <QObject>
#include <QVariant>
#include <QDebug>

#include <antios_gui/infotablemodel.h>
#include <antios_gui/mainwindow.h>

class Application : public QWindow 
{
    Q_OBJECT
public:
    explicit Application(QWindow *parent = nullptr);
    virtual ~Application();

private:
    MainWindow *ui_;
};
