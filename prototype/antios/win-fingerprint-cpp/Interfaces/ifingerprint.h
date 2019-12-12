#ifndef IFINGERPRINT_H
#define IFINGERPRINT_H

#define WOW64_64 "/reg:64"
#define WOW64_32 "/reg:32"

/// @brief IFingerprint - class represents a common interface for system fingerprints
class IFingerprint {
public:
    /// @brief generate - method to save current state, generate random and write to registry
    virtual void generate() = 0;

    /// @brief save_state - saving current state of registry
    virtual void save_state() = 0;

    /// @brief restore_system restore state from backup files
    virtual void restore_state() = 0;

    /// @brief generate a random system state
    virtual void generate_random_state() = 0;

    /// @brief write random generated values to registry
    virtual void write_state() = 0;

    /// @brief object identifier
    virtual bool is_customizable() = 0;

    /// @brief - save branch to reg-file
    virtual bool export_to_file(const std::string &key, const std::string &file, const std::string &reg_mode) = 0;

    /// @brief - resotre key from reg-file
    /// @return pair, first - success resored count, second - count of all files
    virtual std::pair<std::size_t, std::size_t> import_from_files() = 0;
};

#endif // IFINGERPRINT_H
