#pragma once
#include <winfp/fingerprint_data_base.h>
#include <winfp/windows_fpdata.h>

#include <string>
#include <vector>
#include <map>
#include <cstdint>


namespace antios {


class WindowsFingerprint : public antios::FingerprintDataBase
{
public:


    /// @brief Default
    WindowsFingerprint() = default;

    /// @brief Make it polymorph
    virtual ~WindowsFingerprint() = default;

    /// @brief Generate random Windows fingerprint
    virtual void generate() override;

    /// @brief "Retail" or "OEM"
    std::string retail_oem() const;

    /// @brief Windows name without edition, "Windows 7"
    std::string get_product_name() const;

    /// @brief Service pack or major update if present
    std::string get_nt_version() const;

    /// @brief Windows edition, like "Home Premium" or "Professional"
    /// Specific editions should comply with the system version, for example
    /// "Windows 7 Professional N", "Windows 10 Education"
    std::string get_edition() const;

    /// @brief Registry value for EditionID key
    /// Registry value is almost the same as readable, just without spaces
    std::string get_edition_id() const;

    /// @brief ProductName is Windows version and edition with spaces, 
    /// "Windows 7 Professional N"
    std::string get_product_version() const;

    /// @brief Short Windows build version within one product
    /// For example, Windows 7 is "7600", Windows 8.1 is "9600"
    std::string get_short_version() const;

    /// @brief Full Windows build version
    /// For example, Windows 7 is "6.1.7600.16385", Windows 8.1 is "6.3.9600.17031"
    std::string get_full_version() const;

    /// @brief BuildLab string representation
    /// Example: "7601.win7sp1_ldr.170913-0600"
    std::string get_build_lab() const;

    /// @brief BuildLabEx string representation
    /// Example: "7601.23915.amd64fre.win7sp1_ldr.170913-0600"
    std::string get_build_lab_ex() const;

    /// @brief Unix time format, depend on the system release date, 
    /// since installation date can't be before release date
    int get_installation_date() const;

    /// @brief Product ID 
    /// Product ID format is 00376-OEM-166-5442025 for OEM and 04504-455-320-9058939 for Retail
    std::string get_product_id() const;

    /// @brief Add keys, specific for particular system version
    /// For example, "CSDVersion" is specific for Windows 7, "ReleaseId" for Windows 10 
    const std::map<std::string, std::string>& get_system_specific() const;

    /// @brief Build GUID, unique for every build number, random if no info
    std::string get_build_guid() const;

    /// @brief Binary parameter DigitalProductId
    /// Contains a lot of information
    std::vector<uint8_t> digital_product_id() const;

    /// @brief Binary parameter DigitalProductId4
    /// Contains a lot of information
    std::vector<uint8_t> digital_product_id4() const;

    /// @brief Binary array containing installation date
    /// [0x01,0x04] - Unix time, other are random bytes
    /// Should be close enough after installation date
    std::vector<uint8_t> ie_install_date() const;

    /// One of IE updates from the known list, for example "KB3148198"
    std::string ie_service_update() const;

protected:

    /// Generate ProductID
    /// ProductID format is 00376-OEM-166-5442025 for OEM and 04504-455-320-9058939 for Retail
    void generate_product_id();

private:


    /// OEM or Retail version
    bool _oem;

    /// Edition ID, which is base for many other params
    WindowsEditionSKU _edition = WindowsEditionSKU::EditionsCount;

    /// 
    WindowsBuildInfo _build_info;
    
    ///
    int _install_date;

    /// Product ID
    std::string product_id;

    /// Normal GUID
    std::string _build_guid;

    /// GUID for DigitalProductId4
    std::string _build_guid4;

    /// Example for Retail is "00376-166-5442024-86534", for OEM "00438-OEM-5672091-64034"
    std::string _product_id;

    /// Unix time format, should be close enough after installation date
    int _ie_install_date;

    /// One of IE updates from the known list, for example "KB3148198"
    std::string _ie_service_update;
};

} // namespace antios 
