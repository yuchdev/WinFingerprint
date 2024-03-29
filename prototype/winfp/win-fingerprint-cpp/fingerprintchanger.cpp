﻿#include "fingerprintchanger.h"

FingerPrintChanger::FingerPrintChanger()
    : backup_dir_path_("backup\\") {
    std::stringstream ss;
    ss << "You must specify at least one parameter.\n"
       << "For example: \n"
       << "'--telemetry'    Generate Windows 10 Telemetry IDs\n"
       << "'--network'      Generate network-related fingerprint\n"
       << "'--system'       Generate fingerprint based on system version and identifiers\n"
       << "'--hardware'     Generate fingerprint based on hardware identifiers\n"
       << "'--fonts'        Generate fonts fingerprint by redistributing system fonts\n"
       << "'--recover'      Restore registry keys from backups without generation and recording\n"
       << "'--all'          Includes all options excluding restoration\n\n";
    help_string_ = ss.str();
}

FingerPrintChanger::~FingerPrintChanger()
{ }

void FingerPrintChanger::init(int argc, char *argv[]) {
    try {
        if (argc == 1) {
            printf_s("%s", help_string_.data());
            exit(0);
        }

        generators_.insert(std::make_pair(FP::TELEMETRY, (new TelemetryFinregprint  (backup_dir_path_))));
        generators_.insert(std::make_pair(FP::NETWORK,   (new NetworkFingerprint    (backup_dir_path_))));
        generators_.insert(std::make_pair(FP::WINDOWS,   (new WindowsFingerprint    (backup_dir_path_))));
        generators_.insert(std::make_pair(FP::HARDWARE,  (new HardwareFingerprint   (backup_dir_path_))));
        generators_.insert(std::make_pair(FP::FONTS,     (new FontsFingerptint      (backup_dir_path_))));

        if (CMDParser::option_exists(argv, argv+argc, std::string("--recover"))) {
            is_recover_ = true;
        }
        else if (CMDParser::option_exists(argv, argv+argc, std::string("--all"))) {
            is_all_        = true;
            is_telemetry_  = true;
            is_network_    = true;
            is_system_     = true;
            is_hardware_   = true;
            is_fonts_      = true;
        }
        else {
            if (CMDParser::option_exists(argv, argv+argc, std::string("--telemetry"))) is_telemetry_  = true;
            if (CMDParser::option_exists(argv, argv+argc, std::string("--network"  ))) is_network_    = true;
            if (CMDParser::option_exists(argv, argv+argc, std::string("--system"   ))) is_system_     = true;
            if (CMDParser::option_exists(argv, argv+argc, std::string("--hardware" ))) is_hardware_   = true;
            if (CMDParser::option_exists(argv, argv+argc, std::string("--fonts"    ))) is_fonts_      = true;
        }

        if (!is_all_        &&
            !is_telemetry_  &&
            !is_network_    &&
            !is_system_     &&
            !is_hardware_   &&
            !is_fonts_      &&
            !is_recover_    ){
            printf_s("%s", help_string_.data());
            exit(0);
        }

        generate();
    }
    catch (const std::exception& e) { LOG_ERROR << e.what(); }
    catch ( ... ) { LOG_ERROR <<  "Unkown exception in 'FingerPrintChanger'"; }
}


void FingerPrintChanger::save_state() {
    File::remove_all_files(backup_dir_path_);
    try {
        if (is_all_) {
            for (auto &item : generators_) {
                item.second->save_state();
            }
        }
        else {            
            if (is_telemetry_) generators_[FP::TELEMETRY]->save_state();
            if (is_network_  ) generators_[FP::NETWORK  ]->save_state();
            if (is_system_   ) generators_[FP::WINDOWS  ]->save_state();
            if (is_hardware_ ) generators_[FP::HARDWARE ]->save_state();
            if (is_fonts_    ) generators_[FP::FONTS    ]->save_state();
        }
    }
    catch ( ... ) { LOG_ERROR << "Unknown exception in 'save_state'"; }
}


void FingerPrintChanger::restore_state() {
    try {
        if (is_all_) {
            for (auto &item : generators_) {
                item.second->restore_state();
            }
        }
        else {
            if (is_telemetry_) generators_[FP::TELEMETRY]->restore_state();
            if (is_network_  ) generators_[FP::NETWORK  ]->restore_state();
            if (is_system_   ) generators_[FP::WINDOWS  ]->restore_state();
            if (is_hardware_ ) generators_[FP::HARDWARE ]->restore_state();
            if (is_fonts_    ) generators_[FP::FONTS    ]->restore_state();
        }
    }
    catch ( ... ) { }
}


void FingerPrintChanger::generate_random_state() {
    try {
        if (is_all_) {
            for (auto &item : generators_) {
                item.second->generate_random_state();
            }
        }
        else {
            if (is_telemetry_) generators_[FP::TELEMETRY]->generate_random_state();
            if (is_network_  ) generators_[FP::NETWORK  ]->generate_random_state();
            if (is_system_   ) generators_[FP::WINDOWS  ]->generate_random_state();
            if (is_hardware_ ) generators_[FP::HARDWARE ]->generate_random_state();
            if (is_fonts_    ) generators_[FP::FONTS    ]->generate_random_state();
        }
    }
    catch ( ... ) {  }
}

void FingerPrintChanger::generate_custom_state() {
    try {
        if (is_all_) {
            for (auto &item : generators_) {
                item.second->generate_random_state();
            }
        }
        else {
            if (is_telemetry_) generators_[FP::TELEMETRY]->generate_random_state();
            if (is_network_  ) generators_[FP::NETWORK  ]->generate_random_state();
            if (is_system_   ) generators_[FP::WINDOWS  ]->generate_random_state();
            if (is_hardware_ ) generators_[FP::HARDWARE ]->generate_random_state();
            if (is_fonts_    ) generators_[FP::FONTS    ]->generate_random_state();
        }
    }
    catch ( ... ) {  }
}

void FingerPrintChanger::write_state() {
    try {
        if (is_all_) {
            for (auto &item : generators_) {
                item.second->write_state();
            }
        }
        else {
            if (is_telemetry_) generators_[FP::TELEMETRY]->write_state();
            if (is_network_  ) generators_[FP::NETWORK  ]->write_state();
            if (is_system_   ) generators_[FP::WINDOWS  ]->write_state();
            if (is_hardware_ ) generators_[FP::HARDWARE ]->write_state();
            if (is_fonts_    ) generators_[FP::FONTS    ]->write_state();
        }
    }
    catch ( ... ) {  }
}

void FingerPrintChanger::generate() {
    try {
        if (is_recover_) {
            is_all_ = true;
            restore_state();
        }
        else {
            save_state();
            generate_random_state();
            write_state();
        }
    }
    catch (...) {  }
}
