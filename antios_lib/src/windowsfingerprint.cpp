#include <antios_lib/WindowsFingerprint.h>

WindowsFingerprint::WindowsFingerprint(const std::string &backup_dir)
    : backup_dir_path_ { backup_dir + std::string("windows_fp\\") }
    , IE_SERVICE_UPDATES_ { "KB2841134", "KB4088835", "KB4032782", "KB4016446", "KB3210694",
                            "KB3200006", "KB3199375", "KB3192665", "KB4096040", "KB4089187",
                            "KB4074736", "KB4056568", "KB4052978", "KB4047206", "KB4040685",
                            "KB4036586", "KB4034733", "KB4025252", "KB4021558", "KB4018271",
                            "KB4014661", "KB4012204", "KB3185319", "KB3175443", "KB3170106",
                            "KB3160005", "KB3154070", "KB3148198"} {
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
        generate_random_state();
        write_state();
    }
    catch (const std::exception& e) { LOG_ERROR << e.what(); }
    catch ( ... ) { LOG_ERROR << "Unknown exception"; }
}

void WindowsFingerprint::save_state() {
    try {
        if (!File::directory_exists(backup_dir_path_)) {
            File::create_directory_recursively(backup_dir_path_);
        }

        if (helpers::RegistryKey::is_key_exist(CurrentVersion)) {
            helpers::RegistryKey key(CurrentVersion);
            LOG_DEBUG << "Success Open Key: " << CurrentVersion;

            if (export_to_file(CurrentVersion, "CurrentVersion", std::string(WOW64_32))) {

                data_.emplace_back(std::make_pair(std::string("BuildGUID"),             RegItem(CurrentVersion, "BuildGUID",           std::string(), "BuildGUID.dat",             REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("BuildLab"),              RegItem(CurrentVersion, "BuildLab",            std::string(), "BuildLab.dat",              REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("BuildLabEx"),            RegItem(CurrentVersion, "BuildLabEx",          std::string(), "BuildLabEx.dat",            REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("CurrentBuild"),          RegItem(CurrentVersion, "CurrentBuild",        std::string(), "CurrentBuild.dat",          REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("CurrentBuildNumber"),    RegItem(CurrentVersion, "CurrentBuildNumber",  std::string(), "CurrentBuildNumber.dat",    REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("CurrentVersion"),        RegItem(CurrentVersion, "CurrentVersion",      std::string(), "CurrentVersion.dat",        REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("DigitalProductId"),      RegItem(CurrentVersion, "DigitalProductId",    std::string(), "DigitalProductId.dat",      REG_BINARY)));
                data_.emplace_back(std::make_pair(std::string("DigitalProductId4"),     RegItem(CurrentVersion, "DigitalProductId4",   std::string(), "DigitalProductId4.dat",     REG_BINARY)));
                data_.emplace_back(std::make_pair(std::string("EditionID"),             RegItem(CurrentVersion, "EditionID",           std::string(), "EditionID.dat",             REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("InstallDate"),           RegItem(CurrentVersion, "InstallDate",         std::string(), "InstallDate.dat",           REG_DWORD)));
                data_.emplace_back(std::make_pair(std::string("ProductId"),             RegItem(CurrentVersion, "ProductId",           std::string(), "ProductId.dat",             REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("ProductName"),           RegItem(CurrentVersion, "ProductName",         std::string(), "ProductName.dat",           REG_SZ)));
            }
            else { LOG_WARNING << "Key: '" << CurrentVersion << "' not exported, skip..."; }
        }
        else { LOG_WARNING << "Key: '" <<  CurrentVersion << "' not exist! skip..."; }


        if (helpers::RegistryKey::is_key_exist(IEFingerprint)) {
            helpers::RegistryKey key(IEFingerprint);
            LOG_DEBUG << "Success Open Key: " << IEFingerprint;

            if (export_to_file(IEFingerprint, std::string("IEFingerprint"), std::string(WOW64_32))) {

                data_.emplace_back(std::make_pair(std::string("ProductId"),         RegItem(IEFingerprint, "ProductId",         std::string(), "IEProductId",           REG_SZ)));
                data_.emplace_back(std::make_pair(std::string("DigitalProductId"),  RegItem(IEFingerprint, "DigitalProductId",  std::string(), "IEDigitalProductId",    REG_BINARY)));
                data_.emplace_back(std::make_pair(std::string("DigitalProductId4"), RegItem(IEFingerprint, "DigitalProductId4", std::string(), "IEDigitalProductId4",   REG_BINARY)));
            }
            else { LOG_WARNING << "Key: '" << IEFingerprint << "' not exported, skip..."; }
        }
        else { LOG_WARNING << "Key: '" <<  IEFingerprint << "' not exist! skip..."; }

        if (helpers::RegistryKey::is_key_exist(IE)) {
            helpers::RegistryKey key(IE);
            LOG_DEBUG << "Success Open Key: " << IE;

            if (export_to_file(IE, std::string("InternetExplorer"), std::string(WOW64_32))) {
                data_.emplace_back(std::make_pair(std::string("svcKBNumber"), RegItem(IE, "svcKBNumber", std::string(), "IEsvcKBNumber", REG_SZ)));
            }
            else { LOG_WARNING << "Key: '" << IE << "' not exported, skip..."; }
        }

        if (helpers::RegistryKey::is_key_exist(IEMigration)) {
            helpers::RegistryKey key(IEMigration);

            if (export_to_file(IEMigration, std::string("IEMigration"), std::string(WOW64_32))) {
                data_.emplace_back(std::make_pair(std::string("IE Installed Date"), RegItem(IEMigration, "IE Installed Date", std::string(), "IE Installed Date.dat", REG_BINARY)));
                LOG_DEBUG << "SIZE: " << data_.size();
            }
            else { LOG_WARNING << "Key: '" << IEMigration << "' not exported, skip..."; }
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
            if (!write_item(item.second)) {
                LOG_WARNING << "Can't write item: '" << item.second << "' to registry!";
            }
        }
    }
    catch (const std::exception& e) { LOG_ERROR << e.what(); }
    catch ( ... ) { LOG_ERROR << "Unknown exception"; }
}

void WindowsFingerprint::restore_state() {
    if (data_.empty()) return;
    try {
        import_from_files();
    }
    catch (const std::exception& e) { LOG_ERROR << e.what(); }
    catch ( ... ) { LOG_ERROR << "Unknown exception"; }
}

void WindowsFingerprint::generate_random_state() {
    try {
        LOG_DEBUG << "gen 1";
        std::string uuid      = get_random_uuid_id4();
        LOG_DEBUG << "gen 2";
        short windows_version = get_random_windows_version();

        /// bool oem_version      = get_random_oem_version();

        LOG_DEBUG << "gen 3";
        //// get random: product name, current version, curren build, build_lab, build_lab_ex
        std::vector<std::string> blds;
        auto blds_range = BUILDS_.equal_range(windows_version);
        LOG_DEBUG << "gen 4";
        for (auto it = blds_range.first; it != blds_range.second; ++it)
            blds.push_back(it->second);

        LOG_DEBUG << "gen 5";
        if (!save_value("ProductName", get_random_product_name(blds))) {
            LOG_WARNING << "Can't save value: 'ProductName'";
        }
        if (!save_value("BuildLab", get_random_build_lab(blds))) {
            LOG_WARNING << "Can't save value: 'BuildLab'";
        }
        if (!save_value("BuildLabEx", get_random_build_lab_ex(blds))) {
            LOG_WARNING << "Can't save value: 'BuildLabEx'";
        }
        if (!save_value("CurrentBuild", get_random_current_build(blds))) {
            LOG_WARNING << "Can't save value: 'CurrentBuild'";
        }
        if (!save_value("CurrentBuildNumber", get_random_current_build(blds))) {
            LOG_WARNING << "Can't save value: 'CurrentBuildNumber'";
        }
        if (!save_value("CurrentVersion", get_random_current_version(blds))) {
            LOG_WARNING << "Can't save value: 'CurrentVersion'";
        }

        std::vector<std::pair<std::string, std::string>> edts;
        auto edts_range = EDITIONS_.equal_range(windows_version);
        for (auto it1 = edts_range.first; it1 != edts_range.second; ++it1)
            edts.push_back(std::make_pair(it1->second.first, it1->second.second));

        /// get random: edition ID, edition product ID
        std::string rnd_edition_id           = get_random_edition_id            (edts);
        std::string rnd_edition_product_name = get_random_edition_product_name  (edts);

        if (!save_value("EditionID", rnd_edition_id)) {
            LOG_WARNING << "Can't save value 'EditionID'";
        }

        bool oem = false;
        if (rnd_edition_id == "OEM") oem = true;

        if (!save_value("InstallDate", get_random_install_date())) {
            LOG_WARNING << "Can't save value 'InstallDate'";
        }

        std::string retail_oem = get_random_retail_oem(windows_version);

        if (!save_value("BuildGUID", get_random_build_guid(windows_version))) {
            LOG_WARNING << "Can't save value 'BuildGUID'";
        }

        std::string product_id = get_random_product_id(oem);

        if (!save_value("svcKBNumber", get_random_ie_service_update())) {
            LOG_WARNING << "Can't save value 'svcKBNumber'";
        }

        if (!save_value("IE Installed Date", get_random_ie_install_date())) {
            LOG_WARNING << "Can't save value 'IE Installed Date'";
        }
        if (!save_value("ProductId", product_id)) {
            LOG_WARNING << "Can't save value 'ProductId'";
        }
        if (!save_value("DigitalProductId", get_random_digital_product_id(product_id))) {
            LOG_WARNING << "Can't save value 'DigitalProductId'";
        }
        if (!save_value("DigitalProductId4", get_random_digital_product_id4(uuid, retail_oem, rnd_edition_id))) {
            LOG_WARNING << "Can't save value 'DigitalProductId4'";
        }

    }
    catch (const std::exception& e) { LOG_ERROR << e.what(); }
    catch ( ... ) { LOG_ERROR << "Unknown exception"; }
}

bool WindowsFingerprint::is_customizable() { return false; }

void WindowsFingerprint::save_item(const helpers::RegistryKey& root_key, RegItem &item) {
    if (root_key.is_key_exist(item.key_path_)) {
        helpers::RegistryKey key(item.key_path_);
        if (key.is_value_exist(item.value_name_)) {
            switch (item.type_) {
            case REG_SZ:{
                auto result = key.get_string_value(item.value_name_);
                if (result.second) {
                    item.key_value_ = std::move(result.first);
                    data_.push_back(std::make_pair(item.value_name_, item));
                }
                break;
            }
            case REG_DWORD: {
                auto result = key.get_dword_value(item.value_name_);
                if (result.second) {
                    item.key_value_ = std::move(std::to_string(result.first));
                    data_.push_back(std::make_pair(item.value_name_, item));
                }
                break;
            }
            case REG_BINARY: {
                auto result = key.get_binary_value(item.value_name_);
                if (result.second) {
                    item.bin_key_value_ = std::move(result.first);
                    data_.push_back(std::make_pair(item.value_name_, item));
                }
                break;
            }
            default:
                LOG_ERROR << "Wrong type of reg key: '" << item.type_ << "'";
                break;
            }
            LOG_DEBUG << "Save: " << item.value_name_ << " Value: " << item.key_value_;
        }
        else { LOG_WARNING << "Value: '" << item.value_name_ << "' not found. skip..."; }
    }
    else { LOG_WARNING << "Key: '" << item.key_path_ << "' not found. skip...";  }
}


bool WindowsFingerprint::write_item(RegItem &item) {
    LOG_DEBUG << "Try to write key to registry KEY: '" << item.key_path_ << "' VALUE: '" << item.key_value_ << "'";
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
        ok = false;
        break;
    }
    return ok;
}

bool WindowsFingerprint::save_value(const std::string &value_name, const std::string &value) {
    if (data_.empty()) return false;
    LOG_DEBUG << "Try to save ValueName: '" << value_name << "' Value: '" << value << "'";
    try {
        bool result = false;
        for (auto &item : data_) {
            if (item.second.value_name_ == value_name) {
                item.second.key_value_ = value;
                result = true;
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return false;
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return false;
    }
}

bool WindowsFingerprint::save_value(const std::string &value_name, const std::vector<uint8_t> &value) {
    if (data_.empty()) return false;
    LOG_DEBUG << "Try to save ValueName: '" << value_name << "'";
    try {
        bool result = false;
        for (auto &item : data_) {
            if (item.second.value_name_ == value_name) {
                std::copy(value.begin(), value.end(), std::back_inserter(item.second.bin_key_value_));
                result = true;
            }
        }
        return result;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return false;
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return false;
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
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::vector<RegItem>();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::vector<RegItem>();
    }
}

bool WindowsFingerprint::export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) {
    auto result = RegUtil::export_key(key, (backup_dir_path_ + file + ".reg"), reg_mode);
    if (!result.first) { LOG_ERROR << "Can't export key: '" << key << "' Reason: '" << result.second << "'"; }
    else { LOG_INFO << "Success save to file key: '" << key << "' to file: '" << (backup_dir_path_ + file + ".reg") << "'"; }
    return result.first;
}

std::pair<std::size_t, std::size_t> WindowsFingerprint::import_from_files() {
    try {
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
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::make_pair(0, 0);
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::make_pair(0, 0);
    }
}

void WindowsFingerprint::print_binray_value(const std::string &value) {
#ifdef DEBUG
    printf_s("BIN:\n");
    for (std::size_t i(0); i < value.length(); ++i) {
        printf_s("%0.1X ", value[i]);
    }
    printf_s("'\n\n");
#else
    value;
#endif
}

void WindowsFingerprint::print_binray_value(const std::vector<uint8_t> &value) {
#ifdef DEBUG
    printf_s("BIN:\n");
    for (std::size_t i(0); i < value.size(); ++i) {
        printf_s("%0.1X ", value[i]);
    }
    printf_s("'\n\n");
#else
    value;
#endif
}



std::string WindowsFingerprint::get_random_product_name(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    try {
        return blds.at(static_cast<std::size_t>(PRODUCT::PRODUCT_NAME));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_current_version(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    try {
        return blds.at(static_cast<std::size_t>(PRODUCT::CURRENT_VERSION));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_current_build(const std::vector<std::string>& blds) const {
    try {
        if (blds.empty()) return std::string();
        return blds.at(static_cast<std::size_t>(PRODUCT::CURRENT_BUILD));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_build_lab(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    try {
        return blds.at(static_cast<std::size_t>(PRODUCT::BUILD_LAB));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_build_lab_ex(const std::vector<std::string>& blds) const {
    if (blds.empty()) return std::string();
    try {
        return blds.at(static_cast<std::size_t>(PRODUCT::BUILD_LAB_EX));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}



std::string WindowsFingerprint::get_random_edition_id(const std::vector<std::pair<std::string, std::string>>& edts) {
    if (edts.empty()) return std::string();
    try {
        std::uniform_int_distribution<std::size_t> ed_uid(0, edts.size() - 1);
        std::size_t index = ed_uid(rd_);
        return edts.at(index).first;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_edition_product_name(const std::vector<std::pair<std::string, std::string>>& edts) {
    if (edts.empty()) return std::string();
    try {
        std::uniform_int_distribution<std::size_t> ed_uid(0, edts.size() - 1);
        std::size_t index = ed_uid(rd_);
        return edts.at(index).first;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_build_guid(const short win_ver) const {
    try {
        if (win_ver == 7) return SimpleUUID::get_uuid();
        else return std::string("ffffffff-ffff-ffff-ffff-ffffffffffff");
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_uuid_id4() const {
    try {
        return SimpleUUID::get_uuid();
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_ie_service_update() {
    try {
        std::uniform_int_distribution<std::size_t> service_uid(0, IE_SERVICE_UPDATES_.size() - 1);
        return IE_SERVICE_UPDATES_[service_uid(rd_)];
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::vector<uint8_t> WindowsFingerprint::get_random_ie_install_date() {
    try {
        std::uniform_int_distribution<std::size_t> dig_uid(0, 255);
        unsigned long min_timestamp = 1325409822;
        unsigned long max_timestamp = static_cast<unsigned long>(std::time(0));
        std::uniform_int_distribution<unsigned long> time_uid(min_timestamp, max_timestamp);
        unsigned long val = time_uid(rd_);

        std::vector<uint8_t> array(8, 0x00);
        array[0] = (val >> 24) & 0xFF;
        array[1] = (val >> 16) & 0xFF;
        array[2] = (val >> 8)  & 0xFF;
        array[3] = val & 0xFF;
        array[4] = dig_uid(rd_);
        array[5] = dig_uid(rd_);
        array[6] = dig_uid(rd_);
        array[7] = dig_uid(rd_);
        return array;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::vector<uint8_t>();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::vector<uint8_t>();
    }
}

std::string WindowsFingerprint::get_random_install_date() {
    try {
        unsigned long long min_timestamp = 1325409822;
        unsigned long long max_timestamp = std::time(0);
        std::uniform_int_distribution<unsigned long long> time_uid(min_timestamp, max_timestamp);
        return std::to_string(time_uid(rd_));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

std::string WindowsFingerprint::get_random_retail_oem(const bool value) const {
    if (value) return std::string("OEM");
    return std::string("Retail");
}

/// REG_SZ
/// @brief Format of Product ID is a dash-separated string of digits, which lengths consequently 5-3-7-5
/// @return: Windows Product ID
std::string WindowsFingerprint::get_random_product_id(const bool is_oem) {
    try {
        std::uniform_int_distribution<std::size_t> digit_uid(0, digit_string.size() -1);

        std::string pid1;
        std::string pid2;
        std::string pid3;
        std::string pid4;

        for (std::size_t i(0); i < 5; ++i) pid1 += digit_string[digit_uid(rd_)];

        if (is_oem)
            pid2 = "OEM";
        else
            for (std::size_t i(0); i < 3; ++i)
                pid2 += digit_string[digit_uid(rd_)];
        for (std::size_t i(0); i < 7; ++i)
            pid3 += digit_string[digit_uid(rd_)];
        for (std::size_t i(0); i < 5; ++i)
            pid4 += digit_string[digit_uid(rd_)];

        return (pid1 + "-" + pid2 + "-" + pid3 + "-" + pid4);
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::string();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::string();
    }
}

///  5-5-3-6-2-4-4-1rnd-0000-YYYY
std::vector<uint8_t> WindowsFingerprint::get_random_product_id4() {
    try {
        std::uniform_int_distribution<std::size_t> digit_uid(0, digit_string.size() - 1);
        std::uniform_int_distribution<std::size_t> int_uid(0, 3);
        std::uniform_int_distribution<std::size_t> dig_prod_id_uid(0, 255);

        std::vector<uint8_t> prod_os;

        for (std::size_t i(0); i < 5; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));
        prod_os.push_back(static_cast<uint8_t>('-'));
        for (std::size_t i(0); i < 5; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));
        prod_os.push_back(static_cast<uint8_t>('-'));
        for (std::size_t i(0); i < 3; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));
        prod_os.push_back(static_cast<uint8_t>('-'));
        for (std::size_t i(0); i < 6; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));
        prod_os.push_back(static_cast<uint8_t>('-'));
        for (std::size_t i(0); i < 2; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));
        prod_os.push_back(static_cast<uint8_t>('-'));
        for (std::size_t i(0); i < 4; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));
        for (std::size_t i(0); i < 4; ++i)
            prod_os.push_back(static_cast<uint8_t>(digit_string.at(digit_uid(rd_))));

        /// add x00002018
        {
            std::string s("x00002018");
            for (std::size_t i(0); i < s.size(); ++i)
                prod_os.push_back(static_cast<uint8_t>(s[i]));
        }

        prod_os.push_back(static_cast<uint8_t>(dig_prod_id_uid(rd_)));
        prod_os.insert(prod_os.end() - 2, 1, static_cast<uint8_t>(int_uid(rd_)));
        return String::disperse_array(prod_os);;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::vector<uint8_t>();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::vector<uint8_t>();
    }
}

/// REG_BINARY Windows Digital Product ID is 164-bytes length binary
std::vector<uint8_t> WindowsFingerprint::get_random_digital_product_id(const std::string& product_id) {
    std::vector<uint8_t> result(164, 0x00);
    try {
        std::uniform_int_distribution<std::size_t> dig_prod_id_uid(0, 255);

        result[0] = 0xA4;
        result[4] = 0x03;
        result[7] = 0x00;

        /// 8 - 25 prodict_id
        {
            std::size_t i(8);
            std::size_t j(0);
            for ( ; j < product_id.length(); ++i, ++j)
                result[i] = static_cast<uint8_t>(product_id[j]);
        }

        /// 0xA0 (160) - 0xA3 (163)
        result[160] = 0xB9;
        result[161] = 0xEC;
        result[162] = 0x21;
        result[163] = 0x73;
        return result;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return result;
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return result;
    }
}



/// REG_BINARY get digital_product_id4;   total length of array 1272
std::vector<uint8_t> WindowsFingerprint::get_random_digital_product_id4(const std::string& uuid, const std::string& retail_oem, const std::string& rnd_edition_id) {
    std::vector<uint8_t> id4_vec (1272, 0x00);
    try {
        std::uniform_int_distribution<std::size_t> ascii_uid(0, ascii_string.size() - 1);
        std::uniform_int_distribution<std::size_t> digit_uid(0, digit_string.size() - 1);
        std::uniform_int_distribution<std::size_t> int_uid(0, 3);
        std::uniform_int_distribution<std::size_t> dig_prod_id_uid(0, 255);
        std::vector<uint8_t> product_id4 = get_random_product_id4();

        id4_vec[0] = 0xF8;
        id4_vec[1] = 0x04;

        /// start 0x08 - ID (8)
        {
            std::size_t i = 8;
            std::size_t j = 0;
            for ( ; j < product_id4.size(); ++i, ++j)
                id4_vec[i] = product_id4[j];
        }


        /// 0x88 - UUID (136)
        {
            std::string uid = String::disperse_string(uuid);
            std::size_t i = 136;
            std::size_t j = 0;
            for ( ; j < uid.size(); ++i, ++j)
                id4_vec[i] = uid[j];
        }

        /// 0x0118 - Edition (280)
        {
            std::string desp_ed_id = String::disperse_string(rnd_edition_id);
            std::size_t i = 280;
            std::size_t j = 0;
            for ( ; j < desp_ed_id.size(); ++i, ++j)
                id4_vec[i] = desp_ed_id[j];
        }

        /// 0x0328 - random length 80 (808)
        {
            std::size_t i = 808;
            std::size_t j = 0;
            for ( ; j < 80; ++i, ++j)
                id4_vec[i] = static_cast<uint8_t>(dig_prod_id_uid(rd_));
        }

        /// 0x0378 - XNN-NNNNN (888)
        {
            id4_vec[888] = static_cast<uint8_t>(ascii_string[ascii_uid(rd_)]);
            id4_vec[889] = static_cast<uint8_t>(digit_uid(rd_));
            id4_vec[890] = static_cast<uint8_t>(digit_uid(rd_));
            id4_vec[891] = static_cast<uint8_t>('-');
            id4_vec[892] = static_cast<uint8_t>(digit_uid(rd_));
            id4_vec[893] = static_cast<uint8_t>(digit_uid(rd_));
            id4_vec[894] = static_cast<uint8_t>(digit_uid(rd_));
            id4_vec[895] = static_cast<uint8_t>(digit_uid(rd_));
            id4_vec[896] = static_cast<uint8_t>(digit_uid(rd_));
        }

        std::string desp_retail = String::disperse_string(retail_oem);
        /// 0x03F8 - Retail/OEM (1016)
        {
            std::size_t i = 1016;
            std::size_t j = 0;
            for ( ; j < desp_retail.size(); ++i, ++j)
                id4_vec[i] = desp_retail[j];
        }


        /// 0x0478 - Retail/OEM (1144)
        {
            std::size_t i(1144);
            std::size_t j(0);
            for ( ; j < desp_retail.size(); ++i, ++j)
                id4_vec[i] = desp_retail[j];
        }
        return id4_vec;
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return std::vector<uint8_t>();
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return std::vector<uint8_t>();
    }
}

short WindowsFingerprint::get_random_windows_version() {
    try {
        std::uniform_int_distribution<int> ver_uid(0, 2);
        short versions[3] {7, 8, 10};
        return versions[ver_uid(rd_)];
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return -1;
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return -1;
    }
}

bool WindowsFingerprint::get_random_oem_version() {
    try {
        std::uniform_int_distribution<int> uid(0, 1);
        return static_cast<bool>(uid(rd_));
    }
    catch (const std::exception& e) {
        LOG_ERROR << e.what();
        return false;
    }
    catch ( ... ) {
        LOG_ERROR << "Unknown exception";
        return false;
    }
}
