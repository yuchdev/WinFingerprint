#include "networkfingerprint.h"

NetworkFingerprint::NetworkFingerprint(const std::string &backup_dir)
    : backup_dir_path_  (backup_dir + std::string("network-fp\\"))
    , is_custom_        (false)
    , is_valid_         (true ) {
    try {
        users_dictionary_.reset(new Dictionary(std::string("./dic/users.dat")));
        hosts_dictionary_.reset(new Dictionary(std::string("./dic/hosts.dat")));
        macad_dictionary_.reset(new Dictionary(std::string("./dic/macs.dat")));

        if (!users_dictionary_->is_valid() || !hosts_dictionary_->is_valid() || !macad_dictionary_->is_valid())
            is_valid_ = false;
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

NetworkFingerprint::~NetworkFingerprint()
{ }

void NetworkFingerprint::generate() {
    if (!is_valid_) return;
    try {
        save_state();
        if (!is_custom_) {
            write_state();
        }
        else {
            generate_random_state();
            write_state();
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void NetworkFingerprint::save_state() {
    if (!is_valid_) return;
    try {
        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        if (helpers::RegistryKey::is_key_exist(TCPParameters)) {
            helpers::RegistryKey key(TCPParameters);
            if (export_to_file(TCPParameters, std::string("TCPParameters"), std::string(WOW64_64))) {
                data_.emplace_back(std::make_pair(std::string("Hostname"), RegItem(TCPParameters, "Hostname", std::string(), "Hostname", REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("NV Hostname"), RegItem(TCPParameters, "NV Hostname", std::string(), "NV Hostname", REG_SZ)));
            }
            else { LOG_WARNING << "Key: '" << TCPParameters << "' not exported, skip..."; }
        }
        else { LOG_ERROR << " Key: '" << TCPParameters << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(ComputerName)) {
            helpers::RegistryKey key(ComputerName);
            if (export_to_file(ComputerName, std::string("ComputerName"), std::string(WOW64_64))) {
                data_.emplace_back(std::make_pair(std::string("ComputerName"), RegItem(ComputerName, "ComputerName", std::string(), "ComputerName1", REG_SZ)));
            }
            else { LOG_ERROR << " Key: '" << ComputerName << "' not exist!"; }
        }
        else { LOG_ERROR << "Key: '" <<  ComputerName << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(ActiveComputerName)) {
            helpers::RegistryKey key(ActiveComputerName);
            if (export_to_file(ActiveComputerName, std::string("ActiveComputerName"), std::string(WOW64_64))) {
                data_.emplace_back(std::make_pair(std::string("ComputerName"), RegItem(ActiveComputerName, "ComputerName", std::string(), "ComputerName2", REG_SZ)));
            }
            else { LOG_ERROR << " Key: '" << ActiveComputerName << "' not exist!"; }
        }
        else { LOG_ERROR << "Key: '" <<  ActiveComputerName << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(CurrentVersion)) {
            helpers::RegistryKey key(CurrentVersion);
            if (export_to_file(CurrentVersion, std::string("CurrentVersion"), std::string(WOW64_32))) {
                data_.emplace_back(std::make_pair(std::string("RegisteredOwner"), RegItem(CurrentVersion, "RegisteredOwner", std::string(), "RegisteredOwner1", REG_SZ)));
            }
            else { LOG_ERROR << " Key: '" << CurrentVersion << "' not exist!"; }
        }
        else { LOG_ERROR << "Key : '" << CurrentVersion << "' not exist!"; }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void NetworkFingerprint::write_state() {
    if (data_.empty()) return;
    if (!is_valid_) return;
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
    if (!is_valid_) return;
    try {
        std::string rnd_username;
        std::string rnd_hostname;
        std::string rnd_macaddrs;
        do {
            rnd_username = users_dictionary_->get_random_value();
        }
        while (rnd_username.empty());
        do {
            rnd_hostname = hosts_dictionary_->get_random_value();
        }
        while (rnd_hostname.empty());
        do {
            rnd_macaddrs = macad_dictionary_->get_random_value();
        }
        while(rnd_macaddrs.empty());

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
#ifdef DEBUG
        for (auto &it : data_)  LOG_DEBUG << "Random Values: " << it.second;
#endif
    }
    catch ( const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

bool NetworkFingerprint::is_customizable() {
    return true;
}

void NetworkFingerprint::save_item(const helpers::RegistryKey &root_key, RegItem &item) {
    if (!is_valid_) return;
    if (root_key.is_key_exist(item.key_path_)) {
        helpers::RegistryKey key(item.key_path_);
        if (key.is_value_exist(item.value_name_)) {
            switch (item.type_) {
            case REG_SZ: {
                auto result = key.get_string_value(item.value_name_);
                if (result.second) item.key_value_ = std::move(result.first);
            }
                break;
            case REG_DWORD: {
                auto result = key.get_dword_value(item.value_name_);
                if (result.second) item.key_value_ = std::to_string(result.first);
            }
                break;
            case REG_BINARY: {
                auto result = key.get_binary_value(item.value_name_);
                if (result.second) item.bin_key_value_ = std::move(result.first);
            }
                break;
            default:
                LOG_ERROR << "Wrong type of reg key: '" << item << "'";
                break;
            }
            data_.push_back(std::make_pair(std::move(item.value_name_), std::move(item)));
        }
        else { LOG_WARNING << "Value: '" << item.value_name_ << "' not found. skip..."; }
    }
    else { LOG_WARNING << "Key: '" << item.key_path_ << "' not found. skip...";  }
}


bool NetworkFingerprint::write_item(RegItem &item) {
    if (!is_valid_) return false;
    LOG_DEBUG << "Try to write key to registry Param: '" << item.value_name_ << "' VALUE: '" << item.key_value_ << "'";
    helpers::RegistryKey key(item.key_path_);
    bool ok = false;
    switch (item.type_) {
    case REG_SZ:
        ok = key.set_string_value(item.value_name_, item.key_value_);
        break;
    case REG_DWORD:
        ok = key.set_dword_value(item.value_name_, std::stoul(item.key_value_));
        break;
    case REG_BINARY:
        ok = key.set_binary_value(item.value_name_, item.bin_key_value_);
        break;
    default:
        LOG_ERROR << "Wrong type of reg key: '" << item << "'";
        break;
    }
    return ok;
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

bool NetworkFingerprint::export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) {
    if (!is_valid_) return false;
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) { LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'"; }
    else { LOG_INFO << "Success save to file key: '" << key << "'"; }
    return result.first;
}

std::pair<std::size_t, std::size_t> NetworkFingerprint::import_from_files() {
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
        if (!result.first) {
            LOG_ERROR << "Error import from file: '" << item << "' Reason: '" << result.second << "'";
        }
        else {
            LOG_INFO << "Success import from file: " << item << "'";
            ++success_count;
        }
    }
    return std::make_pair(success_count, list_files.size());
}
