#include <QtQuickTest/quicktest.h>
#include <QtQuickTest>
#include <QQmlEngine>
#include <QQmlContext>
#include <QScopedPointer>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QMetaObject>
#include <QQuickView>

///QUICK_TEST_MAIN(test)

#include "../gui/ui/mainwindow.h"
#include "../gui/ui/mainwindow.cpp"

#include "../gui/ui/windowsids.h"
#include "../gui/ui/windowsids.cpp"

#include "../gui/ui/settings.h"
#include "../gui/ui/settings.cpp"

#include "../gui/models/comboboxmodel.h"
#include "../gui/models/comboboxmodel.cpp"

#include "../gui/models/infotablemodel.h"
#include "../gui/models/infotablemodel.cpp"

#include "../gui/types.h"
#include "../gui/application.h"
#include "../gui/application.cpp"

class Setup : public QObject {
    Q_OBJECT
public:
    Setup() = default;
    using QObject::QObject;
public slots:
    void qmlEngineAvailable(QQmlEngine *engine) {
        qmlRegisterType<InfoTableModel> ("InfoTableModel",  1, 0, "InfoTableModel"  );
        qmlRegisterType<Application>    ("MainWindow",     1, 0, "MainWindow"       );

        application.reset(new Application);
        engine->rootContext()->setContextProperty("Application", application.data());

        window.reset(new MainWindow(qobject_cast<QWindow*>(this)));
        engine->rootContext()->setContextProperty("MainWindow", window.data());

        ids.reset(new WindowsIDS(qobject_cast<QWindow*>(this)));
        engine->rootContext()->setContextProperty("WindowsIDS", ids.data());

        engine->rootContext()->setContextProperty("InfoTableModel",      table_model.data()            );
        engine->rootContext()->setContextProperty("SystemNameModel",     SystemNameModel.data()        );
        engine->rootContext()->setContextProperty("ServiceUpdateModel",  ServiceUpdateModel.data()     );
        engine->rootContext()->setContextProperty("EditionModel",        EditionModel.data()           );
        engine->rootContext()->setContextProperty("ProductTypeModel",    ProductTypeNameModel.data()   );
        engine->rootContext()->setContextProperty("BuildNumberModel",    BuildNumberModel.data()       );

    }

private:
    QScopedPointer<Application> application;
    QScopedPointer<MainWindow> window;
    QScopedPointer<WindowsIDS> ids;

    QScopedPointer<InfoTableModel> table_model;
    QScopedPointer<ComboboxModel> SystemNameModel;
    QScopedPointer<ComboboxModel> ServiceUpdateModel;
    QScopedPointer<ComboboxModel> EditionModel;
    QScopedPointer<ComboboxModel> ProductTypeNameModel;
    QScopedPointer<ComboboxModel> BuildNumberModel;
};

QUICK_TEST_MAIN_WITH_SETUP(test, Setup)

#include "tst_qmltests.moc"
