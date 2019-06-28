TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_LFLAGS_RELEASE            += /FORCE:MULTIPLE
QMAKE_LFLAGS_DEBUG              += /FORCE:MULTIPLE


DEFINES += DEBUG
QMAKE_CXXFLAGS_DEBUG += /EHsc

LIBS += -ladvapi32 -lrpcrt4 -lshell32 -lkernel32

SOURCES += \
    main.cpp \
    fingerprintchanger.cpp \
    utils/win_registry_helper.cpp \
    utils/win_system_information.cpp \
    utils/dictionary.cpp \
    Fingerprints/fontsfingerptint.cpp \
    Fingerprints/hardwarefingerprint.cpp \
    Fingerprints/networkfingerprint.cpp \
    Fingerprints/telemetryfinregprint.cpp \
    Fingerprints/windowsfingerprint.cpp

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
    dictionary.h \
    fingerprintchanger.h \
    utils/win_errors.h \
    utils/win_ptrs.h \
    utils/win_registry_helper.h \
    utils/win_system_information.h \
    utils/types.h \
    Interfaces/ifingerprint.h \
    utils/keys.h \
    utils/dictionary.h \
    Interfaces/idictionary.h \
    fingerprintchanger.h \
    Fingerprints/fontsfingerptint.h \
    Fingerprints/hardwarefingerprint.h \
    Fingerprints/networkfingerprint.h \
    Fingerprints/telemetryfinregprint.h \
    Fingerprints/windowsfingerprint.h \
    utils/utils.h

DISTFILES += \
    src/CMakeLists.txt \
    dic/hosts.dat \
    dic/macs.dat \
    dic/users.dat \
    README.md
