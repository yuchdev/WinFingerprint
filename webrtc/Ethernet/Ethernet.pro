TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Base/ethernettoolsbase.cpp \
        ethernettools.cpp \
        main.cpp \
        win32/winethernet.cpp

HEADERS += \
    Base/ethernettoolsbase.h \
    ethernettools.h \
    utils/types.h \
    utils/utils.h \
    win32/winethernet.h


LIBS += -lrpcrt4 \
        -lfwpuclnt \
        -liphlpapi \
        -lws2_32
