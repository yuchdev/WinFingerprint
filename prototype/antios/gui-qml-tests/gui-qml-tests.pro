QT += qml quick testlib
CONFIG += c++14 stl qt warn_on depend_includepath testcase qmltestcase

TEMPLATE = app

SOURCES +=  tst_qmltests.cpp \
    ../gui/application.cpp \
    ../gui/models/comboboxmodel.cpp \
    ../gui/models/infotablemodel.cpp \
    ../gui/ui/mainwindow.cpp \
    ../gui/ui/settings.cpp \
    ../gui/ui/windowsids.cpp

DISTFILES += \
    tst_tests.qml

DEFINES += QT_NO_DEBUG_OUTPUT

MOC_DIR += ./moc

HEADERS += \
    ../gui/application.h \
    ../gui/models/comboboxmodel.h \
    ../gui/models/infotablemodel.h \
    ../gui/types.h \
    ../gui/ui/mainwindow.h \
    ../gui/ui/settings.h \
    ../gui/ui/windowsids.h
