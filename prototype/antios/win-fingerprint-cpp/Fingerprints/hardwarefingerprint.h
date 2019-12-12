#ifndef HARDWAREFINGERPRINT_H
#define HARDWAREFINGERPRINT_H

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

/// @brief - class represents settings system equipment
class HardwareFingerprint : public IFingerprint {
public:
    explicit HardwareFingerprint(const std::string& backup_dir);
    virtual ~HardwareFingerprint();

    void generate               () override;
    void save_state             () override;
    void restore_state          () override;
    void generate_random_state  () override;
    void write_state            () override;
    bool is_customizable        () override;
    std::pair<std::size_t, std::size_t> import_from_files      () override;
    bool export_to_file         (const std::string &key, const std::string &file, const std::string &reg_mode) override;

    /// @brief - save reg-item to container (data_)
    void save_item(const helpers::RegistryKey &root_key, RegItem &item);

    /// @brief - restore reg-item from container (data_)
//    void restore_item(RegItem& item);

    /// @brief - write item to registry
    bool write_item(RegItem& item);
protected:
    /// @brief - directory path for backups
    const std::string backup_dir_path_;
    \
    /// 1st - used reg key 2nd - reg item (all registry entris for hardware)
    std::vector<std::pair<std::string, RegItem>> data_;

    /// @brief - rd_ - random device
    std::random_device rd_;
};

#endif // HARDWAREFINGERPRINT_H
