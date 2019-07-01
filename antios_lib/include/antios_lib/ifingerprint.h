#ifndef IFINGERPRINT_H
#define IFINGERPRINT_H

#define WOW64_64 "/reg:64"
#define WOW64_32 "/reg:32"

/// @brief IFingerprint - class represents a common interface for system fingerprints
class IFingerprint
{
public:
    
    /// @brief Generate method to save current state, generate random and write to registry
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
};

#endif // IFINGERPRINT_H
