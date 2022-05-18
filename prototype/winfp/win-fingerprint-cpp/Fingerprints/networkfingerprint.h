#ifndef NETWORKFINGERPRINT_H
#define NETWORKFINGERPRINT_H

#include <vector>
#include <string>

#include "utils/keys.h"
#include "utils/utils.h"
#include "utils/types.h"
#include "utils/win_ptrs.h"
#include "utils/win_errors.h"
#include "utils/win_registry_helper.h"
#include "utils/win_system_information.h"
#include "utils/dictionary.h"

#include "Interfaces/ifingerprint.h"

/// @brief - the class represent network fingerprint of system
class NetworkFingerprint : public IFingerprint {
public:
    explicit NetworkFingerprint(const std::string& backup_dir);
    virtual ~NetworkFingerprint();

    void generate               () override;
    void save_state             () override;
    void write_state            () override;
    void restore_state          () override;
    void generate_random_state  () override;
    bool is_customizable        () override;

    std::pair<std::size_t, std::size_t> import_from_files() override;

    bool export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) override;

    /// @brief - save reg-item to container (data_)
    void save_item(const helpers::RegistryKey &root_key, RegItem &item);

    /// @brief - write item to registry
    bool write_item(RegItem& item);

    /// @brief - setters of main network id's
    void set_hostname       (const std::string& hostname);
    void set_nvhostname     (const std::string& nvhostname);
    void set_computer_name  (const std::string& computer_name);
    void set_owner          (const std::string& owner);

    /// @brief - getters of main network id;s
    std::string get_hostname        () const;
    std::string get_nvhostname      () const;
    std::string get_computer_name   () const;
    std::string get_owner           () const;

    /// @brief find key in subkey of this branch
    std::vector<RegItem> find_subkey_in_branch(const std::string &branch_name, const std::string& key_name);
protected:
    /// @brief - directory path for backups
    const std::string backup_dir_path_;
    \
    /// 1st - used reg key 2nd - reg item (all registry entris for hardware)
    std::vector<std::pair<std::string, RegItem>> data_;

    /// @brief - rd_ - random device
    std::random_device rd_;

    /// @brief dictionary objects for generating random values of usernames, mac-addresses
    std::unique_ptr<Dictionary> users_dictionary_;
    std::unique_ptr<Dictionary> hosts_dictionary_;
    std::unique_ptr<Dictionary> macad_dictionary_;

    /// @brief - network id's
    std::string hostname_;
    std::string nv_hostname_;
    std::string computer_name_;
    std::string owner_;

    bool is_custom_;
    bool is_valid_;
};

#endif // NETWORKFINGERPRINT_H
