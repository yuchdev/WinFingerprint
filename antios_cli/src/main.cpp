#include <iostream>
#include <algorithm>

#include "plog/Log.h"
#include "plog/Logger.h"
#include "plog/Init.h"
#include "plog/WinApi.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Formatters/FuncMessageFormatter.h"
#include "plog/Formatters/MessageOnlyFormatter.h"

#include <antios_cli/fingerprintchanger.h>

#ifdef DEBUG
    static plog::ColorConsoleAppender<plog::FuncMessageFormatter> console_appender;
    static plog::RollingFileAppender<plog::FuncMessageFormatter> file_appender("fp_changer.log");
#else
    static plog::ColorConsoleAppender<plog::FuncMessageFormatter> console_appender;
#endif

int main(int argc, char* argv[]) 
{
#ifdef DEBUG
    plog::init(plog::debug, &console_appender).addAppender(&file_appender);
#else
    plog::init(plog::info, &console_appender);
#endif
    
    FingerPrintChanger fp_;

    try {
        fp_.init(argc, argv);
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        fp_.restore_state();
    }

    return 0;
}
