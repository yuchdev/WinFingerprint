#ifndef FONTSFINGERPTINT_H
#define FONTSFINGERPTINT_H


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

/// @brief - class represents fonts fingerprint of system
class FontsFingerptint : public IFingerprint {
public:
    explicit FontsFingerptint(const std::string& backup_dir);
    virtual ~FontsFingerptint();

    void generate               () override;
    void save_state             () override;
    void restore_state          () override;
    void generate_random_state  () override;
    void write_state            () override;
    bool is_customizable        () override;

    /// @brief - the method creates a hidden registry branch and moves there a random number of fonts from the main font branch
    void move_fonst_to_hidden(std::size_t size = 0);

    /// @brief - the method returns the moved fonts keys back to the system branch
    void recover_fonts();

    /// @brief - The method allows the user to select the number of fonts to be moved.
    void set_random_size(const std::size_t size);

    /// @brief - getter for count of moved fonts
    std::size_t get_random_size() const;

    /// @brief - save font branch to reg-file
    void export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode);

    /// @brief - resotre all fonts from reg-file
    void import_from_files();

private:
    /// @brief - directory path for backups
    const std::string backup_dir_path_;

    /// @brief 1st - value name, 2nd - value (moved fonts list)
    std::vector<std::pair<std::string, std::string>> random_fonts_;

    /// @brief - list of all fonts from registry
    std::vector<std::pair<std::string, std::string>> all_fonts_;

    /// @brief - random device
    std::random_device rd_;

    /// @brief - count fonts to move
    std::size_t size_;
};

#endif // FONTSFINGERPTINT_H
