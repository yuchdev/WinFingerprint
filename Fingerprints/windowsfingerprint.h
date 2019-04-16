#ifndef WINDOWSFINGERPRINT_H
#define WINDOWSFINGERPRINT_H

#include <map>
#include <vector>
#include <string>

#include "utils/keys.h"
#include "utils/utils.h"
#include "utils/types.h"
#include "utils/win_ptrs.h"
#include "utils/win_errors.h"
#include "utils/win_registry_helper.h"
#include "utils/win_system_information.h"

#include "Interfaces/ifingerprint.h"

enum class EDITION {
    EDITION_ID = 0,
    EDITION_NAME = 1
};

enum class PRODUCT  {
    PRODUCT_NAME    = 0,
    CURRENT_VERSION = 1,
    CURRENT_BUILD   = 2,
    BUILD_LAB       = 3,
    BUILD_LAB_EX    = 4
};

/// @brief - the class represent windows system fingerprint
class WindowsFingerprint : public IFingerprint {
public:
    explicit WindowsFingerprint(const std::string& backup_dir);
    virtual ~WindowsFingerprint();

    void generate               () override;
    void save_state             () override;
    void write_state            () override;
    void restore_state          () override;
    void generate_random_state  () override;
    bool is_customizable        () override;

private:
    /// @brief - save reg-item to container (data_)
    void save_item(const helpers::RegistryKey &root_key, RegItem &item);

    /// @brief - restore reg-item from container (data_)
    void restore_item(RegItem& item);

    /// @brief - write item to registry
    void write_item(RegItem& item);

    /// @brief - save font branch to reg-file
    void export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode);

    /// @brief - resotre all fonts from reg-file
    void import_from_files();

    /// @brief - save generated value to item in data_
    void save_value(const std::string& value_name, const std::string& value);

    /// @brief find key in subkey of this branch
    std::vector<RegItem> find_subkey_in_branch(const std::string &branch_name, const std::string& key_name);

    /// @brief - the metod for printing binary arrays (for testing)
    void print_binray_key(const std::string& value);

private:
    /// @brief - directory path for backups
    const std::string backup_dir_path_;
    \
    /// 1st - used reg key 2nd - reg item (all registry entris for hardware)
    std::vector<std::pair<std::string, RegItem>> data_;

    /// @brief - rd_ - random device
    std::random_device rd_;

    /// @brief - dictionaries for generating random values
    std::multimap<int, std::pair<std::string, std::string>> EDITIONS_;
    std::multimap<int, std::string> BUILDS_;
    const std::vector<std::string> IE_SERVICE_UPDATES_;

    std::string get_random_product_name         (const std::vector<std::string>& blds) const;
    std::string get_random_current_version      (const std::vector<std::string>& blds) const;
    std::string get_random_current_build        (const std::vector<std::string>& blds) const;
    std::string get_random_build_lab            (const std::vector<std::string>& blds) const;
    std::string get_random_build_lab_ex         (const std::vector<std::string>& blds) const;
    std::string get_random_edition_id           (const std::vector<std::pair<std::string, std::string> > &edts);
    std::string get_random_edition_product_name (const std::vector<std::pair<std::string, std::string> > &edts);
    std::string get_random_build_guid           (const short win_ver) const;
    std::string get_random_uuid_id4             () const;
    std::string get_random_ie_service_update    ();
    std::string get_random_ie_install_date      ();
    std::string get_random_install_date         ();
    std::string get_random_retail_oem           (const bool value) const;
    std::string get_random_product_id           (const bool is_oem);
    std::string get_random_digital_product_id   (const std::string& product_id);
    std::string get_random_digital_product_id4  (const std::string& uuid, const std::string& retail_oem, const std::string& rnd_edition_id);
    short get_random_windows_version            ();
    bool get_random_oem_version                 ();

    const std::string digit_string  { "0123456789" };
    const std::string ascii_string  { "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
};

#endif // WINDOWSFINGERPRINT_H
