#include <antios_gui/application.h>

Application::Application(QWindow *parent)
    : QWindow(parent)
    , ui_ (new MainWindow(qobject_cast<QWindow*>(this))) 
{
    qDebug() << "Application()";
}

Application::~Application() 
{
    qDebug() << "~Application()";
}
