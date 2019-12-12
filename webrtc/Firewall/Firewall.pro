TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        firewall.cpp \
        main.cpp \
        win32/wfp.cpp

HEADERS += \
    Base/firewallbase.h \
    firewall.h \
    utils/types.h \
    utils/utils.h \
    win32/wfp.h


LIBS += -lrpcrt4 \
        -lfwpuclnt \
        -liphlpapi \
        -lws2_32
