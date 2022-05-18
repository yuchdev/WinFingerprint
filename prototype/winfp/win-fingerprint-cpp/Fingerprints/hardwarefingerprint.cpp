#include "hardwarefingerprint.h"

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

            if (export_to_file(HwProfileGuid, std::string("HwProfileGuid"), std::string(WOW64_64))) {
                data_.emplace_back(std::make_pair(std::string("HwProfileGuid"), RegItem(HwProfileGuid, "HwProfileGuid", std::string(), "HwProfileGuid1", REG_SZ)));
            }
            else { LOG_WARNING << "Can't save key: '" << HwProfileGuid << "'"; }
        }
        else {
            LOG_ERROR << "Key: '" <<  HwProfileGuid << "' not exist!";
        }


        if (helpers::RegistryKey::is_key_exist(MachineGuid)) {
            helpers::RegistryKey key(MachineGuid);
            if (export_to_file(MachineGuid, std::string("MachineGuid"), std::string(WOW64_64))) {
                data_.emplace_back(std::make_pair(std::string("MachineGuid"), RegItem(MachineGuid, "MachineGuid", std::string(), "MachineGuid", REG_SZ)));
            }
            else { LOG_WARNING << "Can't save key: '" << MachineGuid << "' skip.."; }
        }
        else { LOG_ERROR << "Key: '" <<  MachineGuid << "' not exist!"; }


        if (helpers::RegistryKey::is_key_exist(WindowsUpdate)) {
            helpers::RegistryKey key(WindowsUpdate);
            if (export_to_file(WindowsUpdate, std::string("WindowsUpdate"), std::string(WOW64_64))) {
                data_.emplace_back(std::make_pair(std::string("SusClientId"), RegItem(WindowsUpdate, "SusClientId", std::string(), "SusClientId2", REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("SusClientIDValidation"), RegItem(WindowsUpdate, "SusClientIDValidation", std::string(), "SusClientIDValidation2", REG_BINARY)));
            }
            else { LOG_WARNING << "Can't save key: '" << WindowsUpdate << "' skip..."; }
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
        std::string rnd_uuid_braces = rnd_uuid;
        rnd_uuid_braces.insert(rnd_uuid_braces.begin(), '{');
        rnd_uuid_braces.insert(rnd_uuid_braces.begin() + rnd_uuid_braces.length(), '}');

        for (auto &item : data_) {
            if (item.second.value_name_ == "HwProfileGuid") {
                item.second.key_value_ = rnd_uuid_braces;
            }

            if (item.second.value_name_ == "SusClientId") {
                item.second.key_value_ = rnd_uuid;
            }

            if (item.second.value_name_ == "MachineGuid") {
                item.second.key_value_ = rnd_uuid;
            }

            if (item.second.value_name_ == "SusClientIDValidation") {
                std::vector<uint8_t> array(8, 0x00);

                array[0] = 0x06;
                array[1] = 0x02;
                array[2] = 0x28;
                array[3] = 0x01;

                std::uniform_int_distribution<> ui(1, 255);

                array[4] = static_cast<uint8_t>(ui(rd_));
                array[5] = static_cast<uint8_t>(ui(rd_));
                array[6] = static_cast<uint8_t>(ui(rd_));
                array[7] = 0x00;

                std::string ascii_string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"};
                std::uniform_int_distribution<std::size_t> uid(0, ascii_string.size() -1);
                std::string disp_string;

                for (std::size_t i(0); i < 19; ++i)
                    disp_string += (ascii_string[uid(rd_)]);

                std::string tmp(String::disperse_string(disp_string));

                for (std::size_t i(0); i < tmp.size(); ++i)
                    array.push_back(tmp[i]);

                array.push_back(0x00);
                array.push_back(0x06);
                array.push_back(0x00);

                for (std::size_t i(0); i < 5; ++i)
                    array.push_back(ui(rd_));

                std::string tmp1(String::disperse_string("None"));

                for (std::size_t i(0); i < tmp1.size(); ++i)
                    array.push_back(tmp1[i]);

                array.push_back(0x02);
                array.push_back(0x00);

                item.second.bin_key_value_ = std::move(array);
            }

#ifdef DEBUG
            for (auto &it : data_) LOG_DEBUG << "ITEM: " << it.second;
#endif
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
        if (key.is_value_exist(item.value_name_)) {
            switch (item.type_) {
            case REG_SZ: {
                auto result = key.get_string_value(item.value_name_);
                if (result.second) {
                    item.key_value_ = std::move(result.first);
                    data_.push_back(std::make_pair(item.value_name_, item));
                }
                else { LOG_WARNING << "Can't save parameter: '" << item.value_name_ << "'"; }
            }
                break;
            case REG_DWORD: {
                auto result = key.get_dword_value(item.value_name_);
                if (result.second) {
                    item.key_value_ = std::to_string(result.first);
                    data_.push_back(std::make_pair(item.value_name_, item));
                }
                else { LOG_WARNING << "Can't save parameter: '" << item.value_name_ << "'"; }
            }
                break;
            case REG_BINARY: {
                auto result = key.get_binary_value(item.value_name_);
                if (result.second) {
                    item.bin_key_value_ = std::move(result.first);
                    data_.push_back(std::make_pair(item.value_name_, item));
                }
                else { LOG_WARNING << "Can't save parameter: '" << item.value_name_ << "'"; }
            }
                break;
            default: {
                LOG_ERROR << "Wrong type of reg key: '" << item << "'";
                    break;
            }
            }
        }
        else { LOG_WARNING << "Value: '" << item.value_name_ << "' not found. skip..."; }
    }
    else { LOG_WARNING << "Key: '" << item.key_path_ << "' not found. skip...";  }
}


bool HardwareFingerprint::write_item(RegItem &item) {
    LOG_DEBUG << "Try to write key to registry KEY: '" << item.key_path_ << "' VALUE: '" << item.key_value_ << "'";
    helpers::RegistryKey key(item.key_path_);
    bool result = false;
    switch (item.type_) {
    case REG_SZ: {
        result = key.set_string_value(item.value_name_, item.key_value_);
        break;
    }
    case REG_DWORD: {
        result = key.set_dword_value(item.value_name_, std::stoul(item.key_value_));
        break;
    }
    case REG_BINARY: {
        result = key.set_binary_value(item.value_name_, item.bin_key_value_);
        break;
    }
    default:
        LOG_ERROR << "Wrong type of reg key: '" << item << "'";
        break;
    }
    return result;
}

bool HardwareFingerprint::export_to_file(const std::string& key, const std::string& file, const std::string& reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) { LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'"; }
    else { LOG_INFO << "Success save to file key: '" << key << "'"; }
    return result.first;
}

std::pair<std::size_t, std::size_t> HardwareFingerprint::import_from_files() {
    auto list_files = File::list_files_in_directory(backup_dir_path_);
    std::size_t success_count = 0;
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

        if (!result.first) { LOG_ERROR << "Error import from file: '" << item << "' Reason: '" << result.second << "'"; }
        else {
            LOG_INFO << "Success import from file: " << item << "'";
            ++success_count;
        }
    }
    return std::make_pair(success_count, list_files.size());
}
