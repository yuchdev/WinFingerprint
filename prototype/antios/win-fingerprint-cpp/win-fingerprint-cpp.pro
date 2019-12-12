# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = win-fingerprint-cpp

HEADERS = \
   $$PWD/Fingerprints/fontsfingerptint.h \
   $$PWD/Fingerprints/hardwarefingerprint.h \
   $$PWD/Fingerprints/networkfingerprint.h \
   $$PWD/Fingerprints/telemetryfinregprint.h \
   $$PWD/Fingerprints/windowsfingerprint.h \
   $$PWD/Interfaces/idictionary.h \
   $$PWD/Interfaces/ifingerprint.h \
   $$PWD/plog/Appenders/AndroidAppender.h \
   $$PWD/plog/Appenders/ColorConsoleAppender.h \
   $$PWD/plog/Appenders/ConsoleAppender.h \
   $$PWD/plog/Appenders/DebugOutputAppender.h \
   $$PWD/plog/Appenders/EventLogAppender.h \
   $$PWD/plog/Appenders/IAppender.h \
   $$PWD/plog/Appenders/RollingFileAppender.h \
   $$PWD/plog/Converters/NativeEOLConverter.h \
   $$PWD/plog/Converters/UTF8Converter.h \
   $$PWD/plog/Formatters/CsvFormatter.h \
   $$PWD/plog/Formatters/FuncMessageFormatter.h \
   $$PWD/plog/Formatters/MessageOnlyFormatter.h \
   $$PWD/plog/Formatters/TxtFormatter.h \
   $$PWD/plog/Init.h \
   $$PWD/plog/Log.h \
   $$PWD/plog/Logger.h \
   $$PWD/plog/Record.h \
   $$PWD/plog/Severity.h \
   $$PWD/plog/Util.h \
   $$PWD/plog/WinApi.h \
   $$PWD/utils/dictionary.h \
   $$PWD/utils/keys.h \
   $$PWD/utils/types.h \
   $$PWD/utils/utils.h \
   $$PWD/utils/win_errors.h \
   $$PWD/utils/win_ptrs.h \
   $$PWD/utils/win_registry_helper.h \
   $$PWD/utils/win_system_information.h \
   $$PWD/fingerprintchanger.h

SOURCES = \
   $$PWD/Fingerprints/fontsfingerptint.cpp \
   $$PWD/Fingerprints/hardwarefingerprint.cpp \
   $$PWD/Fingerprints/networkfingerprint.cpp \
   $$PWD/Fingerprints/telemetryfinregprint.cpp \
   $$PWD/Fingerprints/windowsfingerprint.cpp \
   $$PWD/utils/dictionary.cpp \
   $$PWD/utils/utils.cpp \
   $$PWD/utils/win_registry_helper.cpp \
   $$PWD/utils/win_system_information.cpp \
   $$PWD/.gitignore \
   $$PWD/fingerprintchanger.cpp \
   $$PWD/main.cpp \
   $$PWD/msvc_make.bat \
   $$PWD/README.md \
   $$PWD/win_fingerprint-cpp.pro

INCLUDEPATH = \
    $$PWD/. \
    $$PWD/Fingerprints \
    $$PWD/Interfaces \
    $$PWD/plog \
    $$PWD/plog/Appenders \
    $$PWD/plog/Converters \
    $$PWD/plog/Formatters \
    $$PWD/utils

#DEFINES = 

