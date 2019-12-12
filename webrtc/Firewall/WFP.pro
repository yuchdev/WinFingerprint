TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Base/ethernettoolsbase.cpp \
        Base/firewallbase.cpp \
        ethernettools.cpp \
        firewall.cpp \
        main.cpp \
        win32/wfp.cpp \
        win32/winethernet.cpp

HEADERS += \
    Base/ethernettoolsbase.h \
    Base/firewallbase.h \
    ethernettools.h \
    firewall.h \
    utils/types.h \
    utils/utils.h \
    win32/wfp.h \
    win32/winethernet.h


LIBS += -lrpcrt4 \
        -lfwpuclnt \
        -liphlpapi \
        -lws2_32
