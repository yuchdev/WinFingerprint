#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QVariant>
#include <QDebug>

#include <antios_gui/infotablemodel.h>
#include <antios_gui/mainwindow.h>

class Application : public QWindow {
    Q_OBJECT
public:
    explicit Application(QWindow *parent = nullptr);
    virtual ~Application();

signals:
public slots:
private:
    MainWindow *ui_;
};

#endif // APPLICATION_H

