#include <antios_lib/hardwarefingerprint.h>

HardwareFingerprint::HardwareFingerprint(const std::string& backup_dir)
    : backup_dir_path_(backup_dir + std::string("hardware_fp\\"))
{
}

HardwareFingerprint::~HardwareFingerprint()
{ }

void HardwareFingerprint::generate() {
    try {
        save_state();
        generate_random_state();
        write_state();
    }
    catch ( const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void HardwareFingerprint::save_state() {
    try {
        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        if (helpers::RegistryKey::is_key_exist(HwProfileGuid)) {
            helpers::RegistryKey key(HwProfileGuid);

            export_to_file(HwProfileGuid, std::string("HwProfileGuid"), std::string(WOW64_64));

            RegItem hw_guid(HwProfileGuid, "HwProfileGuid", std::string(), "HwProfileGuid1", REG_SZ);
            RegItem hw_susclient(HwProfileGuid, "SusClientId", std::string(), "SusClientId1", REG_SZ);
            RegItem hw_suse_validation(HwProfileGuid, "SusClientIDValidation", std::string(), "SusClientIDValidationfa1", REG_BINARY);

            save_item(key, hw_guid);
            save_item(key, hw_susclient);
            save_item(key, hw_suse_validation);
        }
        else { LOG_ERROR << "Key: '" <<  HwProfileGuid << "' not exist!"; }


        if (helpers::RegistryKey::is_key_exist(MachineGuid)) {
            helpers::RegistryKey key(MachineGuid);
            export_to_file(MachineGuid, std::string("MachineGuid"), std::string(WOW64_64));
            RegItem m_guid(MachineGuid, "MachineGuid", std::string(), "MachineGuid", REG_SZ);
            save_item(key, m_guid);
        }
        else { LOG_ERROR << "Key: '" <<  MachineGuid << "' not exist!"; }


        if (helpers::RegistryKey::is_key_exist(WindowsUpdate)) {
            helpers::RegistryKey key(WindowsUpdate);
            export_to_file(WindowsUpdate, std::string("WindowsUpdate"), std::string(WOW64_64));
            RegItem sus_client_id(WindowsUpdate, "SusClientId", std::string(), "SusClientId2", REG_SZ);
            RegItem sus_client_validation_id(WindowsUpdate, "SusClientIDValidation", std::string(), "SusClientIDValidation2", REG_BINARY);
            save_item(key, sus_client_id);
            save_item(key, sus_client_validation_id);
        }
        else {  LOG_ERROR << "Key: '" <<  WindowsUpdate << "' not exist!";  }
        /// TODO: Implament VlumeID change!
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void HardwareFingerprint::restore_state() {
    try {
        import_from_files();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}

void HardwareFingerprint::generate_random_state() {
    try {
        std::string rnd_uuid(SimpleUUID::get_uuid());

        for (auto &item : data_) {
            if (item.second.value_name_ == "HwProfileGuid") {
                item.second.key_value_ = rnd_uuid;
            }

            if (item.second.value_name_ == "SusClientId") {
                item.second.key_value_ = rnd_uuid;
            }

            if (item.second.value_name_ == "MachineGuid") {
                item.second.key_value_ = rnd_uuid;
            }

            if (item.second.value_name_ == "SusClientIDValidation") {
                std::vector<unsigned char> array;
                for (std::size_t i(0); i < 8; ++i)
                    array.push_back(0);

                array.push_back(0x06);
                array.push_back(0x02);
                array.push_back(0x28);
                array.push_back(0x01);

                std::uniform_int_distribution<> ui(1, 255);

                array.push_back(ui(rd_));
                array.push_back(ui(rd_));
                array.push_back(ui(rd_));

                array.push_back(0);

                std::string ascii_string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
                std::uniform_int_distribution<std::size_t> uid(0, ascii_string.size() -1);
                std::string disp_string;

                for (std::size_t i(0); i < 19; ++i)
                    disp_string += (ascii_string[uid(rd_)]);

                std::string tmp(String::disperse_string(disp_string));

                for (std::size_t i(0); i < tmp.size(); ++i)
                    array.push_back(tmp[i]);

                array.push_back(0);
                array.push_back(6);
                array.push_back(0);

                for (std::size_t i(0); i < 5; ++i)
                    array.push_back(ui(rd_));

                std::string tmp1(String::disperse_string("None"));

                for (std::size_t i(0); i < tmp1.size(); ++i)
                    array.push_back(tmp1[i]);

                std::stringstream ss;
                for (auto &it: array) { ss << it; }
                item.second.key_value_ = ss.str();
            }
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}

void HardwareFingerprint::write_state() {
    if (data_.empty()) return;
    try {
        for (auto &item : data_) {
            write_item(item.second);
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}

bool HardwareFingerprint::is_customizable() {
    return false;
}

void HardwareFingerprint::save_item(const helpers::RegistryKey &root_key, RegItem &item) {
    if (root_key.is_key_exist(item.key_path_)) {
        helpers::RegistryKey key(item.key_path_);
        if (key.is_value_exists(item.value_name_)) {
            switch (item.type_) {
            case REG_SZ:
                item.key_value_ = key.get_string_value(item.value_name_);
                break;
            case REG_DWORD:
                item.key_value_ = std::to_string(key.get_dword_value(item.value_name_));
                break;
            case REG_BINARY:
                item.key_value_ = key.get_binary_value(item.value_name_);
                break;
            default:
                LOG_ERROR << "Wrong type of reg key: '" << item << "'";
                break;
            }
            data_.push_back(std::make_pair(item.value_name_, item));
        }
        else { LOG_WARNING << "Value: '" << item.value_name_ << "' not found. skip..."; }
    }
    else { LOG_WARNING << "Key: '" << item.key_path_ << "' not found. skip...";  }
}

void HardwareFingerprint::restore_item(RegItem &item) {
    helpers::RegistryKey key (item.key_path_);
    LOG_DEBUG << "Try to restore: " << backup_dir_path_ + item.file_name_ << "  KEY: " << item.key_path_;
    auto res = key.restore_value(backup_dir_path_, item.file_name_);
    if (!res.first) {
        LOG_ERROR << "Can't restore: " << item.file_name_ << "  Error: " << res.second;
    }
    else {
        LOG_INFO << "Success restore: " << item.value_name_ << " From: " << item.file_name_;
    }
}

void HardwareFingerprint::write_item(RegItem &item) {
    LOG_DEBUG << "Try to write key to registry KEY: '" << item.key_path_ << "' VALUE: '" << item.key_value_ << "'";
    helpers::RegistryKey key(item.key_path_);
    switch (item.type_) {
    case REG_SZ:
        key.set_string_value(item.value_name_, item.key_value_);
        break;
    case REG_DWORD:
        key.set_dword_value(item.value_name_, std::stoul(item.key_value_));
        break;
    case REG_BINARY:
        key.set_binary_value(item.value_name_, item.key_value_);
        break;
    default:
        LOG_ERROR << "Wrong type of reg key: '" << item << "'";
        break;
    }
}

void HardwareFingerprint::export_to_file(const std::string& key, const std::string& file, const std::string& reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) {
        LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'";
    }
    else {
        LOG_INFO << "Success save to file key: '" << key << "'";
    }
}

void HardwareFingerprint::import_from_files() {
    auto list_files = File::list_files_in_directory(backup_dir_path_);
    for (auto &item : list_files) {
        std::pair<bool, std::string> result;
        std::size_t max_count = 1000;
        std::size_t current_ = 0;
        do {
            if (current_ > max_count) break;
            result = RegUtil::import_key(item);
            current_++;
        }
        while (!result.first);
        if (!result.first) {
            LOG_ERROR << "Error import from file: '" << item << "' Reason: '" << result.second << "'";
        }
        else {
            LOG_INFO << "Success import from file: " << item << "'";
        }
    }
}
