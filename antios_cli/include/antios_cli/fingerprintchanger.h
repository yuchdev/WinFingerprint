#ifndef FINGERPRINTCHANGER_H
#define FINGERPRINTCHANGER_H

#include <memory>

#include <utils/utils.h>

#include <antios_lib/telemetryfinregprint.h>
#include <antios_lib/fontsfingerptint.h>
#include <antios_lib/hardwarefingerprint.h>
#include <antios_lib/networkfingerprint.h>
#include <antios_lib/windowsfingerprint.h>

#include <plog/Log.h>
#include <plog/Logger.h>

enum class FP {
    TELEMETRY   = 0,
    NETWORK     = 1,
    WINDOWS     = 2,
    HARDWARE    = 3,
    FONTS       = 4
};

class FingerPrintChanger {
public:
    explicit FingerPrintChanger();
    virtual ~FingerPrintChanger();

    void init(int argc, char *argv[]);

    void save_state();
    void restore_state();
    void generate_random_state ();
    void generate_custom_state();
    void write_state();
    void generate();

private:
    /// @brief fingerprints objects
    std::map<FP, std::unique_ptr<IFingerprint>> generators_;

    const std::string backup_dir_path_;
    std::string help_string_;

    bool is_all_        = false;
    bool is_telemetry_  = false;
    bool is_network_    = false;
    bool is_system_     = false;
    bool is_hardware_   = false;
    bool is_fonts_      = false;
};

#endif // FINGERPRINTCHANGER_H
