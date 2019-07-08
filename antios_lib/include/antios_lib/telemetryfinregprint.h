#ifndef TELEMETRYFINREGPRINT_H
#define TELEMETRYFINREGPRINT_H

#include <vector>
#include <string>

#include "utils/keys.h"
#include "utils/utils.h"
#include "utils/types.h"
#include "utils/win_ptrs.h"
#include "utils/win_errors.h"
#include "utils/win_registry_helper.h"
#include "utils/win_system_information.h"

#include <antios_lib/ifingerprint.h>
#include "utils/utils.h"

/// @brief - the class is a fingerprint system for telemetry (windows 10 only)
class TelemetryFinregprint : public IFingerprint {
public:
    explicit TelemetryFinregprint(const std::string& backup_dir_path_);
    virtual ~TelemetryFinregprint();

    void generate               () override;
    void save_state             () override;
    void write_state            () override;
    void restore_state          () override;
    void generate_random_state  () override;
    bool is_customizable        () override;
    bool export_to_file         (const std::string &key, const std::string &file, const std::string &reg_mode) override;
    std::pair<std::size_t, std::size_t> import_from_files() override;

    /// @brief - write item to registry
    bool write_item(RegItem& item);

    /// @brief find key in subkey of this branch
    std::vector<RegItem> find_subkey_in_branch(const std::string &branch_name, const std::string& key_name);

protected:
    /// @brief - directory path for backups
    const std::string backup_dir_path_;
    \
    /// 1st - used reg key 2nd - reg item (all registry entris for hardware)
    std::vector<std::pair<std::string, RegItem>> data_;
};

#endif // TELEMETRYFINREGPRINT_H
