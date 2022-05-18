TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#DESTDIR     += $$PWD/build-tests/
#TARGET      += $$PWD/build-tests/bin/tests.exe
#OBJECTS_DIR += $$PWD/build-tests/obj
#MOC_DIR     += $$PWD/build-tests/moc

#TARGET += TESTS

QMAKE_LFLAGS_RELEASE  += /FORCE:MULTIPLE
QMAKE_LFLAGS_DEBUG    += /FORCE:MULTIPLE
#QMAKE_CXXFLAGS        += /Gz

DEFINES += DEBUG

LIBS += -ladvapi32 -lrpcrt4 -lshell32 -lkernel32

QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
QMAKE_CXXFLAGS_STL_ON = /EHa

DEFINES += DEBUG

LIBS += -ladvapi32 -lrpcrt4 -lshell32 -lkernel32

INCLUDEPATH += C:/Boost/include/

SOURCES += \
        main.cpp

win32: LIBS += -LC:/Boost/lib/x86/lib/ -llibboost_unit_test_framework-vc140-mt-gd-x32-1_70

INCLUDEPATH += C:/Boost/lib/x86
DEPENDPATH += C:/Boost/lib/x86

win32: LIBS += -LC:/Boost/lib/x86/lib/ -llibboost_date_time-vc140-mt-gd-x32-1_70

INCLUDEPATH += C:/Boost/lib/x86
DEPENDPATH += C:/Boost/lib/x86
