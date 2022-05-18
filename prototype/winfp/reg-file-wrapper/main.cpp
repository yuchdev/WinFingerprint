#include <iostream>

#include "plog/Log.h"
#include "plog/Logger.h"
#include "plog/Init.h"
#include "plog/WinApi.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Appenders/RollingFileAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "plog/Formatters/FuncMessageFormatter.h"
#include "plog/Formatters/MessageOnlyFormatter.h"

#include "regfile.h"
#include <string>

#include "utils/win_registry_helper.h"

#ifdef DEBUG
static plog::ColorConsoleAppender<plog::FuncMessageFormatter> console_appender;
static plog::RollingFileAppender<plog::FuncMessageFormatter> file_appender("debug.log");
#else
static plog::ColorConsoleAppender<plog::FuncMessageFormatter> console_appender;
#endif

int main() {

#ifdef DEBUG
    plog::init(plog::debug, &console_appender).addAppender(&file_appender);
#else
    plog::init(plog::info, &console_appender);
#endif

    try {
        std::string test_path("./Backup_dir");
        if (helpers::RegistryKey::is_key_exist(HwProfileGuid)) {
            helpers::RegistryKey key(HwProfileGuid);
            auto value = key.get_string_value("HwProfileGuid");
            if (value.second) {
                std::string val = value.first;
                RegItem reg(HwProfileGuid, std::string("HwProfileGuid"), val, std::string("HwProfile.dat"), REG_SZ);
                LOG_DEBUG << "Item to write: " << reg.to_string();
                RegFile reg_file(test_path, reg);
                reg_file.write();

                LOG_DEBUG << "Read File: " << reg_file.read().to_string();
            }
            else {
                LOG_WARNING << "Get string value is fail";
            }
        }
        else { LOG_ERROR << "Key '" + HwProfileGuid + "' does not exist!"; }

        if (helpers::RegistryKey::is_key_exist(WindowsUpdate)) {
            helpers::RegistryKey key(WindowsUpdate);
            auto value = key.get_binary_value("SusClientIDValidation");
            if (value.second) {
                RegItem reg(WindowsUpdate, std::string("SusClientIDValidation"), "",
                            std::string("SusClientIDValidation.dat"), REG_BINARY);
                reg.bin_value_ = value.first;
                LOG_DEBUG << "Item to write: " << reg.to_string();
                RegFile reg_file(test_path, reg);
                reg_file.write();

                LOG_DEBUG << "Read File: " << reg_file.read().to_string();
            }
            else {
                LOG_WARNING << "Get bin value is fail";
            }
        }
        else { LOG_ERROR << "Key '" + WindowsUpdate + "' does not exist!"; }
        return 0;
    }
    catch (const std::exception &e) {
        LOG_FATAL << e.what();
        return -1;
    }
    catch (...) {
        LOG_FATAL << "Unknown exception!";
        return -1;
    }
}
