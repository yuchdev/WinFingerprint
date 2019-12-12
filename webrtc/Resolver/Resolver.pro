TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        resolver.cpp \
        win32/winresolver.cpp

HEADERS += \
    Base/resolverbase.h \
    resolver.h \
    win32/winresolver.h

LIBS += -lws2_32
