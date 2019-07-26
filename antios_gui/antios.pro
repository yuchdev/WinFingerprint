QT += quick qml core quickwidgets
CONFIG += qt c++17 stl qml_debug #console
QT -= network
QT -= svg
TARGET += antios_gui

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QT_QML_DEBUG

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/include

win32 {
   QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
   QMAKE_CXXFLAGS_STL_ON = /EHa
}

QMAKE_LFLAGS_RELEASE            += /FORCE:MULTIPLE
QMAKE_LFLAGS_DEBUG              += /FORCE:MULTIPLE
QMAKE_LFLAGS_RELEASE            += /IGNORE:4006
QMAKE_LFLAGS_DEBUG              += /IGNORE:4006

QMAKE_CXXFLAGS_WARN_OFF += -w34100 -wd4100 -w4100

SOURCES += \
        src/application.cpp \
        src/application.cpp \
        src/main.cpp \
        src/comboboxmodel.cpp \
        src/comboboxmodel.cpp \
        src/infotablemodel.cpp \
        src/infotablemodel.cpp \
        src/mainwindow.cpp \
        src/mainwindow.cpp \
        src/settings.cpp \
        src/windowsids.cpp \
        src/windowsids.cpp

RESOURCES += antios.qrc \
#    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/antios_gui/application.h \
    include/antios_gui/comboboxmodel.h \
    include/antios_gui/infotablemodel.h \
    include/antios_gui/types.h \
    include/antios_gui/mainwindow.h \
    include/antios_gui/settings.h \
    include/antios_gui/windowsids.h

DISTFILES += \
    src/Windows_ids.qml \
    src/Windows_idsForm.ui.qml \
    src/Settings.qml \
    src/SettingsForm.ui.qml \
    src/Windows_ids.qml \
    src/Windows_idsForm.ui.qml \
    src/main.qml \
    res/next.png
