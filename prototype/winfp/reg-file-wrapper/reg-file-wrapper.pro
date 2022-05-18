TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS_RELEASE  += /FORCE:MULTIPLE
QMAKE_LFLAGS_DEBUG    += /FORCE:MULTIPLE

DEFINES += DEBUG

LIBS += -ladvapi32 -lrpcrt4 -lshell32 -lkernel32

win32 {
   QMAKE_CXXFLAGS_EXCEPTIONS_ON = /EHa
   QMAKE_CXXFLAGS_STL_ON = /EHa
}

SOURCES += \
        main.cpp \
        regfile.cpp \
        utils/utils.cpp \
        utils/win_registry_helper.cpp \
        utils/win_system_information.cpp

HEADERS += \
    plog/Appenders/AndroidAppender.h \
    plog/Appenders/ColorConsoleAppender.h \
    plog/Appenders/ConsoleAppender.h \
    plog/Appenders/DebugOutputAppender.h \
    plog/Appenders/EventLogAppender.h \
    plog/Appenders/IAppender.h \
    plog/Appenders/RollingFileAppender.h \
    plog/Converters/NativeEOLConverter.h \
    plog/Converters/UTF8Converter.h \
    plog/Formatters/CsvFormatter.h \
    plog/Formatters/FuncMessageFormatter.h \
    plog/Formatters/MessageOnlyFormatter.h \
    plog/Formatters/TxtFormatter.h \
    plog/Init.h \
    plog/Log.h \
    plog/Logger.h \
    plog/Record.h \
    plog/Severity.h \
    plog/Util.h \
    plog/WinApi.h \
    regfile.h \
    utils/keys.h \
    utils/types.h \
    utils/utils.h \
    utils/win_errors.h \
    utils/win_ptrs.h \
    utils/win_registry_helper.h \
    utils/win_system_information.h

