#include <antios_lib/networkfingerprint.h>

NetworkFingerprint::NetworkFingerprint(const std::string &backup_dir)
    : backup_dir_path_  (backup_dir + std::string("network-fp\\"))
    , is_custom_        (false)
{
    try {
        users_dictionary_.reset(new Dictionary(std::string("./dic/users.dat")));
        hosts_dictionary_.reset(new Dictionary(std::string("./dic/hosts.dat")));
        macad_dictionary_.reset(new Dictionary(std::string("./dic/macs.dat")));
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

NetworkFingerprint::~NetworkFingerprint() {

}

void NetworkFingerprint::generate() {
    try {
        save_state();
        if (!is_custom_) {
            generate_random_state();
        }
        write_state();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void NetworkFingerprint::save_state() {
    try {
        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        if (helpers::RegistryKey::is_key_exist(TCPParameters)) {
            helpers::RegistryKey key(TCPParameters);
            export_to_file(TCPParameters, std::string("TCPParameters"), std::string(WOW64_64));
            RegItem hostname_item(TCPParameters, "Hostname", std::string(), "Hostname", REG_SZ);
            RegItem nv_hostname_item(TCPParameters, "NV Hostname", std::string(), "NV_Hostname", REG_SZ);
            save_item(key, hostname_item);
            save_item(key, nv_hostname_item);
        }
        else { LOG_ERROR << " Key: '" << TCPParameters << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(ComputerName)) {
            helpers::RegistryKey key(ComputerName);
            export_to_file(ComputerName, std::string("ComputerName"), std::string(WOW64_64));
            RegItem comp_name(ComputerName, "ComputerName", std::string(), "ComputerName1", REG_SZ);
            save_item(key, comp_name);
        }
        else { LOG_ERROR << "Key: '" <<  ComputerName << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(ActiveComputerName)) {
            helpers::RegistryKey key(ActiveComputerName);
            export_to_file(ActiveComputerName, std::string("ActiveComputerName"), std::string(WOW64_64));
            RegItem comp_name(ActiveComputerName, "ComputerName", std::string(), "ComputerName2", REG_SZ);
            save_item(key, comp_name);
        }
        else { LOG_ERROR << "Key: '" <<  ActiveComputerName << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(CurrentVersion)) {
            helpers::RegistryKey key(CurrentVersion);
            export_to_file(CurrentVersion, std::string("CurrentVersion"), std::string(WOW64_32));
            LOG_DEBUG << "Success Open Key: " << CurrentVersion;
            RegItem owner(CurrentVersion, "RegisteredOwner", std::string(), "RegisteredOwner1", REG_SZ);
            save_item(key, owner);
        }
        else { LOG_ERROR << "Key : '" << CurrentVersion << "' not exist!"; }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void NetworkFingerprint::write_state() {
    if (data_.empty()) return;
    try {
        for (auto &item : data_) {
            write_item(item.second);
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknow exception!"; }
}

void NetworkFingerprint::restore_state() {
    if (data_.empty()) return;
    try {
        import_from_files();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void NetworkFingerprint::generate_random_state() {
    if (data_.empty()) return;
    try {
        std::string rnd_username = users_dictionary_->get_random_value();
        std::string rnd_hostname = hosts_dictionary_->get_random_value();
        std::string rnd_macaddrs = macad_dictionary_->get_random_value();

        LOG_DEBUG << "Random Username: " << rnd_username;
        LOG_DEBUG << "Random Hostname: " << rnd_hostname;
        LOG_DEBUG << "Random macaddrs: " << rnd_macaddrs;

        for ( auto &item : data_) {
            if (item.second.value_name_ == "NV Hostname") {
                item.second.key_value_ = rnd_hostname;
            }

            if (item.second.value_name_ == "Hostname") {
                item.second.key_value_ = rnd_hostname;
            }

            if (item.second.value_name_ == "ComputerName") {
                item.second.key_value_ = rnd_hostname;
            }

            if (item.second.value_name_ == "RegisteredOwner") {
                item.second.key_value_ = rnd_username;
            }
        }

        for (auto &it : data_) {
            LOG_DEBUG << "Random Values: " << it.second;
        }
    }
    catch ( const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

bool NetworkFingerprint::is_customizable() {
    return true;
}

void NetworkFingerprint::save_item(const helpers::RegistryKey &root_key, RegItem &item) {
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

void NetworkFingerprint::restore_item(RegItem &item) {
    LOG_DEBUG << "Try to restore: " << backup_dir_path_ + item.file_name_;

    helpers::RegistryKey key (item.key_path_);
    auto res = key.restore_value(backup_dir_path_, item.file_name_);
    if (!res.first) {
        LOG_ERROR << "Can't restore: " << item.file_name_ << "  Error: " << res.second;
    }
    else {
        LOG_INFO << "Success restore: " << item.value_name_ << " From: " << item.file_name_;
    }
}

void NetworkFingerprint::write_item(RegItem &item) {
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


void NetworkFingerprint::set_hostname(const std::string &hostname) {
    if (!hostname.empty() && hostname != hostname_) {
        hostname_ = hostname;
    }
}

void NetworkFingerprint::set_nvhostname(const std::string &nvhostname) {
    if (!nvhostname.empty() && nv_hostname_ != nvhostname) {
        nv_hostname_ = nvhostname;
    }
}

void NetworkFingerprint::set_computer_name(const std::string &computer_name) {
    if (!computer_name.empty() && computer_name != computer_name_) {
        computer_name_ = computer_name;
    }
}

void NetworkFingerprint::set_owner(const std::string &owner) {
    if (!owner.empty() && owner != owner_) {
        owner_ = owner;
    }
}

std::string NetworkFingerprint::get_hostname() const {
    return hostname_;
}

std::string NetworkFingerprint::get_nvhostname() const {
    return nv_hostname_;
}

std::string NetworkFingerprint::get_computer_name() const {
    return computer_name_;
}

std::string NetworkFingerprint::get_owner() const {
    return owner_;
}

void NetworkFingerprint::export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) {
        LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'";
    }
    else {
        LOG_INFO << "Success save to file key: '" << key << "'";
    }
}

void NetworkFingerprint::import_from_files() {
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
