TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        pinger.cpp \
        win32/winpinger.cpp

HEADERS += \
    Base/pingerbase.h \
    pinger.h \
    pingerbase.h \
    win32/winpinger.h

LIBS += -lIphlpapi \
        -lws2_32
