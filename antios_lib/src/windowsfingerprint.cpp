#include <antios_lib/WindowsFingerprint.h>

WindowsFingerprint::WindowsFingerprint(const std::string &backup_dir)
    : backup_dir_path_ { backup_dir + std::string("windows_fp\\") }
    , IE_SERVICE_UPDATES_ { "KB2841134", "KB4088835", "KB4032782", "KB4016446", "KB3210694",
                            "KB3200006", "KB3199375", "KB3192665", "KB4096040", "KB4089187",
                            "KB4074736", "KB4056568", "KB4052978", "KB4047206", "KB4040685",
                            "KB4036586", "KB4034733", "KB4025252", "KB4021558", "KB4018271",
                            "KB4014661", "KB4012204", "KB3185319", "KB3175443", "KB3170106",
                            "KB3160005", "KB3154070", "KB3148198"}
{
    EDITIONS_.insert(std::make_pair(7, std::make_pair("Starter", "Starter")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("HomeBasic", "Home Basic")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("HomePremium", "Home Premium")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("Professional", "Professional")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("ProfessionalN", "Professional N")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("ProfessionalKN", "Professional KN")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("Enterprise", "Enterprise")));
    EDITIONS_.insert(std::make_pair(7, std::make_pair("Ultimate", "Ultimate")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("Core", "Core")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("Pro", "Pro")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("ProN", "Pro N")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("Enterprise", "Enterprise")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("EnterpriseN", "Enterprise N")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("OEM", "OEM")));
    EDITIONS_.insert(std::make_pair(8, std::make_pair("withBing", "with Bing")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("Home", "Home")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("Pro", "Pro")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("ProEducation", "Pro Education")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("Enterprise", "Enterprise")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("EnterpriseLTSB", "Enterprise LTSB")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("Education", "Education")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("IoTCore", "IoT Core")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("IoTEnterprise", "IoT Enterprise")));
    EDITIONS_.insert(std::make_pair(10, std::make_pair("S", "S")));

    BUILDS_.insert(std::make_pair(7, "Windows 7"));
    BUILDS_.insert(std::make_pair(7, "6.1"));
    BUILDS_.insert(std::make_pair(7, "7601"));
    BUILDS_.insert(std::make_pair(7, "7601.win7sp1_ldr.170913-0600"));
    BUILDS_.insert(std::make_pair(7, "7601.23915.amd64fre.win7sp1_ldr.170913-0600"));
    BUILDS_.insert(std::make_pair(8, "Windows 8.1"));
    BUILDS_.insert(std::make_pair(8, "7.1"));
    BUILDS_.insert(std::make_pair(8, "9600"));
    BUILDS_.insert(std::make_pair(8, "9600.winblue_r4.141028-1500"));
    BUILDS_.insert(std::make_pair(8, "9600.17415.amd64fre.winblue_r4.141028-1500"));
    BUILDS_.insert(std::make_pair(10, "Windows 10"));
    BUILDS_.insert(std::make_pair(10, "9.0"));
    BUILDS_.insert(std::make_pair(10, "16299"));
    BUILDS_.insert(std::make_pair(10, "16299.rs3_release.170928-1534"));
    BUILDS_.insert(std::make_pair(10, "16299.15.amd64fre.rs3_release.170928-1534"));
}

WindowsFingerprint::~WindowsFingerprint()
{ }

void WindowsFingerprint::generate() {
    try {
        save_state();
//        generate_random_state(); //// test!!!
        write_state();
    }
    catch ( const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void WindowsFingerprint::save_state() {
    try {
        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        if (helpers::RegistryKey::is_key_exist(CurrentVersion)) {
            helpers::RegistryKey key(CurrentVersion);
            LOG_DEBUG << "Success Open Key: " << CurrentVersion;

            export_to_file(CurrentVersion, "CurrentVersion", std::string(WOW64_32));

            RegItem BuildGUID           (CurrentVersion, "BuildGUID",           std::string(), "BuildGUID.dat",             REG_SZ);
            RegItem BuildLab            (CurrentVersion, "BuildLab",            std::string(), "BuildLab.dat",              REG_SZ);
            RegItem BuildLabEx          (CurrentVersion, "BuildLabEx",          std::string(), "BuildLabEx.dat",            REG_SZ);
            RegItem CurrentBuild        (CurrentVersion, "CurrentBuild",        std::string(), "CurrentBuild.dat",          REG_SZ);
            RegItem CurrentBuildNumber  (CurrentVersion, "CurrentBuildNumber",  std::string(), "CurrentBuildNumber.dat",    REG_SZ);
            RegItem CurrentVersion1     (CurrentVersion, "CurrentVersion",      std::string(), "CurrentVersion.dat",        REG_SZ);
            RegItem DigitalProductId    (CurrentVersion, "DigitalProductId",    std::string(), "DigitalProductId.dat",      REG_BINARY);
            RegItem DigitalProductId4   (CurrentVersion, "DigitalProductId4",   std::string(), "DigitalProductId4.dat",     REG_BINARY);
            RegItem EditionID           (CurrentVersion, "EditionID",           std::string(), "EditionID.dat",             REG_SZ);
            RegItem InstallDate         (CurrentVersion, "InstallDate",         std::string(), "InstallDate.dat",           REG_DWORD);
            RegItem ProductId           (CurrentVersion, "ProductId",           std::string(), "ProductId.dat",             REG_SZ);
            RegItem ProductName         (CurrentVersion, "ProductName",         std::string(), "ProductName.dat",           REG_SZ);
            RegItem RegisteredOwner     (CurrentVersion, "RegisteredOwner",     std::string(), "RegisteredOwner.dat",       REG_SZ);

            save_item(key, BuildGUID);
            save_item(key, BuildLab);
            save_item(key, BuildLabEx);
            save_item(key, CurrentBuild);
            save_item(key, CurrentBuildNumber);
            save_item(key, CurrentVersion1);
            save_item(key, DigitalProductId);
            save_item(key, DigitalProductId4);
            save_item(key, EditionID);
            save_item(key, InstallDate);
            save_item(key, ProductId);
            save_item(key, ProductName);
            save_item(key, RegisteredOwner);
        }
        else { LOG_ERROR << "Key: '" <<  CurrentVersion << "' not exist!"; }


        if (helpers::RegistryKey::is_key_exist(IEFingerprint)) {
            helpers::RegistryKey key(IEFingerprint);
            LOG_DEBUG << "Success Open Key: " << IEFingerprint;

            export_to_file(IEFingerprint, std::string("IEFingerprint"), std::string(WOW64_32));

            RegItem svcKBNumber         (IEFingerprint, "svcKBNumber",       std::string(), "IEsvcKBNumber.dat",          REG_SZ);
            RegItem ProductId           (IEFingerprint, "ProductId",         std::string(), "IEProductId.dat",            REG_SZ);
            RegItem DigitalProductId    (IEFingerprint, "DigitalProductId",  std::string(), "IEDigitalProductId.dat",     REG_BINARY);
            RegItem DigitalProductId4   (IEFingerprint, "DigitalProductId4", std::string(), "IEDigitalProductId4.dat",    REG_BINARY);

            save_item(key, svcKBNumber);
            save_item(key, ProductId);
            save_item(key, DigitalProductId);
            save_item(key, DigitalProductId4);
        }
        else { LOG_ERROR << "Key: '" <<  IEFingerprint << "' not exist!"; }

        if (helpers::RegistryKey::is_key_exist(IEMigration)) {
            helpers::RegistryKey key(IEMigration);

            export_to_file(IEMigration, std::string("IEMigration"), std::string(WOW64_32));

            RegItem ie_installed_date(IEMigration, "IE Installed Date", std::string(), "IE Installed Date.dat", REG_BINARY);
            save_item(key, ie_installed_date);
        }
        else { LOG_ERROR << "Key: '" <<  IEMigration << "' not exist!"; }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception!"; }
}

void WindowsFingerprint::write_state() {
    if (data_.empty()) return;
    try {
        for (auto &item : data_) {
            write_item(item.second);
        }
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}

void WindowsFingerprint::restore_state() {
    if (data_.empty()) return;
    try {

        import_from_files();
    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}

void WindowsFingerprint::generate_random_state() {
    try {
        std::string uuid      = get_random_uuid_id4();
        short windows_version = get_random_windows_version();
        bool oem_version      = get_random_oem_version();

        //// get random: product name, current version, curren build, build_lab, build_lab_ex
        std::vector<std::string> blds;
        auto blds_range = BUILDS_.equal_range(windows_version);
        for (auto it = blds_range.first; it != blds_range.second; ++it)
            blds.push_back(it->second);

        save_value("ProductName",        get_random_product_name    (blds));
        save_value("BuildLab",           get_random_build_lab       (blds));
        save_value("BuildLabEx",         get_random_build_lab_ex    (blds));
        save_value("CurrentBuild",       get_random_current_build   (blds));
        save_value("CurrentBuildNumber", get_random_current_build   (blds));
        save_value("CurrentVersion",     get_random_current_version (blds));

        std::vector<std::pair<std::string, std::string>> edts;
        auto edts_range = EDITIONS_.equal_range(windows_version);
        for (auto it1 = edts_range.first; it1 != edts_range.second; ++it1)
            edts.push_back(std::make_pair(it1->second.first, it1->second.second));

        /// get random: edition ID, edition product ID
        std::string rnd_edition_id           = get_random_edition_id            (edts);
        std::string rnd_edition_product_name = get_random_edition_product_name  (edts);

        save_value("EditionID", rnd_edition_id);

        bool oem = false;
        if (rnd_edition_id == "OEM") oem = true;

        save_value("InstallDate", get_random_install_date());

        std::string retail_oem = get_random_retail_oem(windows_version);

        save_value("BuildGUID", get_random_build_guid(windows_version));

        std::string product_id = get_random_product_id(oem);

        save_value("svcKBNumber",       get_random_ie_service_update());
        save_value("IE Installed Date", get_random_install_date());
        save_value("DigitalProductId",  get_random_digital_product_id(product_id));
        save_value("ProductId",         product_id);
        save_value("DigitalProductId4", get_random_digital_product_id4(uuid, retail_oem, rnd_edition_id));

    }
    catch (const std::exception& e) { throw std::exception(e); }
    catch ( ... ) { throw "Unknown exception"; }
}

bool WindowsFingerprint::is_customizable() {
    return false;
}

void WindowsFingerprint::save_item(const helpers::RegistryKey& root_key, RegItem &item) {
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

            /// save to binary file
            /// auto res = key.save_value(backup_dir_path_, item.file_name_);
            /// if (!res.first) {
            ///     LOG_ERROR << "Cant't save value: '" << item.value_name_ << "' Error: '" << res.second << "'";
            /// }
            /// else {
            ///     LOG_INFO << "Success save to File Name: '" << item.file_name_ << "'";
            /// }

            data_.push_back(std::make_pair(item.value_name_, item));
            LOG_DEBUG << "Save: " << item.value_name_ << " Value: " << item.key_value_;
        }
        else { LOG_WARNING << "Value: '" << item.value_name_ << "' not found. skip..."; }
    }
    else { LOG_WARNING << "Key: '" << item.key_path_ << "' not found. skip...";  }
}

void WindowsFingerprint::restore_item(RegItem &item) {
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

void WindowsFingerprint::write_item(RegItem &item) {
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

void WindowsFingerprint::save_value(const std::string &value_name, const std::string &value) {
    if (data_.empty()) return;
    for (auto &item : data_) {
        if (item.second.value_name_ == value_name) {
            item.second.key_value_ = value;
        }
    }
}

std::vector<RegItem> WindowsFingerprint::find_subkey_in_branch(const std::string &branch_name, const std::string &key_name) {
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
                            std::string value = k.get_string_value(val);
                            result.emplace_back(RegItem((branch_name + "\\" + it), key_name, value, (it + "." + key_name), 0));
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

void WindowsFingerprint::export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) {
        LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'";
    }
    else {
        LOG_INFO << "Success save to file key: '" << key << "' to file: '" << (backup_dir_path_ + file + ".reg") << "'";
    }
}

void WindowsFingerprint::import_from_files() {
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

void WindowsFingerprint::print_binray_key(const std::string &value) {
#ifdef DEBUG
    printf_s("BIN:\n");
    for (std::size_t i(0); i < value.length(); ++i) {
        printf_s("%0.1X ", value[i]);
    }
    printf_s("'\n\n");
#endif
}

std::string WindowsFingerprint::get_random_product_name(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    return blds.at(static_cast<std::size_t>(PRODUCT::PRODUCT_NAME));
}

std::string WindowsFingerprint::get_random_current_version(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    return blds.at(static_cast<std::size_t>(PRODUCT::CURRENT_VERSION));
}

std::string WindowsFingerprint::get_random_current_build(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    return blds.at(static_cast<std::size_t>(PRODUCT::CURRENT_BUILD));
}

std::string WindowsFingerprint::get_random_build_lab(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    return blds.at(static_cast<std::size_t>(PRODUCT::BUILD_LAB));
}

std::string WindowsFingerprint::get_random_build_lab_ex(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    return blds.at(static_cast<std::size_t>(PRODUCT::BUILD_LAB_EX));
}



std::string WindowsFingerprint::get_random_edition_id(const std::vector<std::pair<std::string, std::string>>& edts) {
    if (edts.empty()) return std::string();
    std::uniform_int_distribution<std::size_t> ed_uid(0, edts.size() - 1);
    std::size_t index = ed_uid(rd_);
    return edts.at(index).first;
}

std::string WindowsFingerprint::get_random_edition_product_name(const std::vector<std::pair<std::string, std::string>>& edts) {
    if (edts.empty()) return std::string();
    std::uniform_int_distribution<std::size_t> ed_uid(0, edts.size() - 1);
    std::size_t index = ed_uid(rd_);
    return edts.at(index).first;
}

std::string WindowsFingerprint::get_random_build_guid(const short win_ver) const {
    if (win_ver == 7) return SimpleUUID::get_uuid();
    else return std::string("ffffffff-ffff-ffff-ffff-ffffffffffff");
}

std::string WindowsFingerprint::get_random_uuid_id4() const {
    return SimpleUUID::get_uuid();
}

std::string WindowsFingerprint::get_random_ie_service_update() {
    std::uniform_int_distribution<std::size_t> service_uid(0, IE_SERVICE_UPDATES_.size() - 1);
    return IE_SERVICE_UPDATES_[service_uid(rd_)];
}

std::string WindowsFingerprint::get_random_ie_install_date() {
    unsigned long long min_timestamp = 1325409822;
    unsigned long long max_timestamp = std::time(0);
    std::uniform_int_distribution<unsigned long long> time_uid(min_timestamp, max_timestamp);
    return std::to_string(time_uid(rd_));
}

std::string WindowsFingerprint::get_random_install_date() {
    unsigned long long min_timestamp = 1325409822;
    unsigned long long max_timestamp = std::time(0);
    std::uniform_int_distribution<unsigned long long> time_uid(min_timestamp, max_timestamp);
    return std::to_string(time_uid(rd_));
}

std::string WindowsFingerprint::get_random_retail_oem(const bool value) const {
    if (value) return std::string("OEM");
    return std::string("Retail");
}

std::string WindowsFingerprint::get_random_product_id(const bool is_oem) {
    std::uniform_int_distribution<std::size_t> digit_uid(0, digit_string.size() -1);
    std::string pid1;
    std::string pid2;
    std::string pid3;
    std::string pid4;

    for (std::size_t i(0); i < 5; ++i)
        pid1 += digit_string[digit_uid(rd_)];

    if (is_oem) pid2 = "OEM";
    else for (std::size_t i(0); i < 3; ++i) pid2 += digit_string[digit_uid(rd_)];
    for (std::size_t i(0); i < 7; ++i) pid3 += digit_string[digit_uid(rd_)];
    for (std::size_t i(0); i < 5; ++i) pid4 += digit_string[digit_uid(rd_)];

    return (pid1 + "-" + pid2 + "-" + pid3 + "-" + pid4);
}

std::string WindowsFingerprint::get_random_digital_product_id(const std::string& product_id) {
    std::ostringstream os;
    std::uniform_int_distribution<std::size_t> dig_prod_id_uid(0, 255);
    for (std::size_t i(0); i < 164; ++i) {
        os << dig_prod_id_uid(rd_);
    }
    os << 0xA4 << 0x0 << 0x0 << 0x0 << 0x3 << 0x0 << 0x0 << 0x0 << product_id;
    return os.str();
}

std::string WindowsFingerprint::get_random_digital_product_id4(const std::string& uuid, const std::string& retail_oem, const std::string& rnd_edition_id) {
    /// 5-5-3-6-2-4-4-1rnd-0000-YYYY
    std::uniform_int_distribution<std::size_t> digit_uid(0, digit_string.size() -1);
    std::uniform_int_distribution<std::size_t> ascii_uid(0, ascii_string.size() -1);
    std::uniform_int_distribution<std::size_t> dig_prod_id_uid(0, 255);

    std::ostringstream prod_os;
    for (std::size_t i(0); i < 5; ++i)
        prod_os << digit_string[digit_uid(rd_)];
    prod_os << "-";
    for (std::size_t i(0); i < 3; ++i)
        prod_os << digit_string[digit_uid(rd_)];
    prod_os << "-";
    for (std::size_t i(0); i < 6; ++i)
        prod_os << digit_string[digit_uid(rd_)];
    prod_os << "-";
    for (std::size_t i(0); i < 2; ++i)
        prod_os << digit_string[digit_uid(rd_)];
    prod_os << "-";
    for (std::size_t i(0); i < 4; ++i)
        prod_os << digit_string[digit_uid(rd_)];
    prod_os << "-";
    for (std::size_t i(0); i < 4; ++i)
        prod_os << digit_string[digit_uid(rd_)];
    prod_os << "x00002018";
    std::string prod_id4 = prod_os.str();

    /// get digital_product_id4;
    std::ostringstream id4_os;
    for (std::size_t i(0); i < 1272; ++i) id4_os << 0;
    id4_os << 0xF8 << 0x04 << prod_id4;
    id4_os << String::disperse_string(uuid);
    id4_os << String::disperse_string(id4_os.str());
    id4_os << String::disperse_string(rnd_edition_id);

    for (std::size_t i(0); i < 80; ++i)
        id4_os << dig_prod_id_uid(rd_);

    std::ostringstream os;
    os << std::toupper(ascii_string.at(ascii_uid(rd_)), std::locale());
    os << digit_string[digit_uid(rd_)];
    os << digit_string[digit_uid(rd_)];
    os << "-";
    os << digit_string[digit_uid(rd_)];
    os << digit_string[digit_uid(rd_)];
    os << digit_string[digit_uid(rd_)];

    id4_os << String::disperse_string(os.str());
    id4_os << String::disperse_string(retail_oem);
    id4_os << String::disperse_string(retail_oem);

    return id4_os.str();
}

short WindowsFingerprint::get_random_windows_version() {
    std::uniform_int_distribution<int> ver_uid(0, 2);
    short versions[3] {7, 8, 10};
    return versions[ver_uid(rd_)];
}

bool WindowsFingerprint::get_random_oem_version() {
    std::uniform_int_distribution<int> uid(0, 2);
    return static_cast<bool>(uid(rd_) % 2);
}
