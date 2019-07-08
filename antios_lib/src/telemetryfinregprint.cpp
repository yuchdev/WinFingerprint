#include <antios_lib/telemetryfinregprint.h>

TelemetryFinregprint::TelemetryFinregprint(const std::string &backup_dir_path)
    : backup_dir_path_(backup_dir_path + std::string("telemetry_fp\\"))
{ }

TelemetryFinregprint::~TelemetryFinregprint()
{ }

void TelemetryFinregprint::generate() {
    try {
        save_state();
        generate_random_state();
        write_state();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void TelemetryFinregprint::save_state() {
    try {

        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        RegItem sqm_client_item;
        sqm_client_item.key_path_   = SQMClient;
        sqm_client_item.value_name_ = std::string("MachineId");
        sqm_client_item.file_name_  = sqm_client_item.value_name_;
        sqm_client_item.type_       = REG_SZ;

        if (helpers::RegistryKey::is_key_exist(sqm_client_item.key_path_)) {
            helpers::RegistryKey key(sqm_client_item.key_path_);
            if (key.is_value_exist(sqm_client_item.value_name_)) {
                auto result = key.get_string_value(sqm_client_item.value_name_);
                if (result.second) {
                    sqm_client_item.key_value_ = std::move(result.first);
                    export_to_file(sqm_client_item.key_path_, sqm_client_item.value_name_, std::string(WOW64_64));
                    data_.emplace_back(std::make_pair(sqm_client_item.value_name_, sqm_client_item));
                }
                else { LOG_WARNING << "Can't get value: '" << sqm_client_item.value_name_ << "'"; }
            }
            else { LOG_WARNING << "Value: '" << sqm_client_item.value_name_ << "' not found, skip..."; }
        }
        else { LOG_ERROR << "Skip branch: '" << sqm_client_item.key_path_ << "'"; }


        if (helpers::RegistryKey::is_key_exist(SettingsRequests)) {
            std::string ETagQueryParameters("ETagQueryParameters");
            export_to_file(SettingsRequests, std::string("SettingsRequests"), std::string(WOW64_64));
            auto data_to_save = find_subkey_in_branch(SettingsRequests, ETagQueryParameters);
            if (!data_to_save.empty()) {
                for (auto &data_item : data_to_save) {
                    if (helpers::RegistryKey::is_key_exist(data_item.key_path_)) {
                        helpers::RegistryKey sub_key(data_item.key_path_);
                        auto result = sub_key.get_string_value(data_item.value_name_);
                        if (result.second) {
                            data_item.key_value_ = std::move(result.first);
                            data_item.type_ = REG_SZ;
                            data_.emplace_back(std::make_pair(ETagQueryParameters, data_item));
                        }
                    }
                }
            }
            else { LOG_WARNING << "Value: '" << ETagQueryParameters << "' not found, skip..."; }
        }
        else { LOG_ERROR << "Skip branch: '" << SettingsRequests << "'"; }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}


void TelemetryFinregprint::write_state() {
    if (data_.empty()) return;
    try {
        for (auto &item : data_) {
            write_item(item.second);
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknow exception!"; }
}


void TelemetryFinregprint::restore_state() {
    try {
        import_from_files();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}


void TelemetryFinregprint::generate_random_state() {
    if (data_.empty()) return;
    try {
        std::string uuid = SimpleUUID::get_uuid();
        for (auto &item : data_) {
            if (item.first == "MachineId") {
                item.second.key_value_ = uuid;
            }

            if (item.first == "ETagQueryParameters") {
                std::size_t found = item.second.key_value_.find(':');
                if (found != std::string::npos) {
                    item.second.key_value_.replace(found + 1, found + 36, uuid);
                }
            }
        }

        LOG_INFO << "After randomize : ";
        for (auto &it : data_)  LOG_INFO << it.second;
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}


bool TelemetryFinregprint::is_customizable() {
    return false;
}


bool TelemetryFinregprint::write_item(RegItem &item) {
    LOG_DEBUG << "Try to write key to registry KEY: '" << item.key_path_ << "' VALUE: '" << item.key_value_ << "'";
    helpers::RegistryKey key(item.key_path_);
    bool result = false;
    switch (item.type_) {
    case REG_SZ:
        result = key.set_string_value(item.value_name_, item.key_value_);
        break;
    case REG_DWORD:
        result = key.set_dword_value(item.value_name_, std::stoul(item.key_value_));
        break;
    case REG_BINARY:
        result = key.set_binary_value(item.value_name_, item.bin_key_value_);
        break;
    default:
        LOG_ERROR << "Wrong type of reg key: '" << item << "'";
        break;
    }
    return result;
}


std::vector<RegItem> TelemetryFinregprint::find_subkey_in_branch(const std::string &branch_name, const std::string &key_name) {
    try {
        std::vector<RegItem> result;
        if (helpers::RegistryKey::is_key_exist(branch_name)) {
            helpers::RegistryKey key(branch_name);
            auto list = key.enumerate_subkeys();
            for (auto &it : list) {
                if (helpers::RegistryKey::is_key_exist(branch_name + "\\" + it)) {
                    helpers::RegistryKey sub_key(branch_name + "\\" + it);
                    auto subvals = sub_key.enumerate_values();
                    for (auto &val : subvals) {
                        if (val == key_name) {
                            helpers::RegistryKey k((branch_name + "\\" + it));
                            auto res = k.get_string_value(val);
                            if (res.second) {
                                result.emplace_back(RegItem((branch_name + "\\" + it), key_name, res.first, (it + "." + key_name), 0));
                            }
                        }
                    }
                }
            }
        }
        return result;
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

bool TelemetryFinregprint::export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) { LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'"; }
    else { LOG_INFO << "Success save to file key: '" << key << "'"; }
    return result.first;
}

std::pair<std::size_t, std::size_t> TelemetryFinregprint::import_from_files() {
    auto list = File::list_files_in_directory(backup_dir_path_);
    std::size_t success_count = 0;
    for (auto &it : list) {
        std::pair<bool, std::string> result;
        std::size_t max_count = 1000;
        std::size_t current_ = 0;
        do {
            if (current_ > max_count) break;
            result = RegUtil::import_key(it);
            current_++;
        }
        while (!result.first);
        if (!result.first) {
            LOG_ERROR << "Error import from file: '" << it << "' Reason: '" << result.second << "'";
        }
        else {
            LOG_INFO << "Success import from file: " << it << "'";
            ++success_count;
        }
    }
    return std::make_pair(success_count, list.size());
}
