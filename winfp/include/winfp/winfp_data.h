#pragma once
#include <winfp/fingerprint_data_base.h>

#include <string>
#include <vector>
#include <map>
#include <cstdint>


namespace antios {

    enum class WindowsEditionSKU
    {
        Starter = 0,
        HomeBasic = 1,
        HomePremium = 2,
        Professional = 3,
        ProfessionalN = 4,
        ProfessionalKN = 5,
        Ultimate = 6,
        Core = 7,
        Pro = 8,
        ProN = 9,
        Enterprise = 10,
        EnterpriseN = 11,
        OEM = 12,
        WithBing = 13,
        Home = 14,
        ProEducation = 15,
        EnterpriseLTSB = 16,
        Education = 17,
        IoTCore = 18,
        IoTEnterprise = 19,
        S = 20,
        EditionsCount
    };

    enum class WindowsBuild
    {
        Windows_6_1_7600_16385,
        Windows_6_1_7600_17514,
        Windows_6_1_7600_24214
    };

    struct WindowsBuildNumber
    {
        WindowsBuildNumber(int kernel_version,
            int major_version,
            int minor_version,
            int build_number) :
            _kernel_version(kernel_version),
            _major_version(major_version),
            _minor_version(minor_version),
            _build_number(build_number) {}

        int _kernel_version = 0;
        int _major_version = 0;
        int _minor_version = 0;
        int _build_number = 0;
    };

    class WindowsFingerprint : public antios::FingerprintDataBase
    {
    public:

        /// @brief Default
        WindowsFingerprint() = default;

        /// @brief Make it polymorph
        virtual ~WindowsFingerprint() = default;

        /// @brief
        virtual void generate() override;

        /// @brief Windows major version, [7, 8, 10]
        int system_version() const;

        /// @brief Windows name without edition, "Windows 7"
        std::string system_name() const;

        /// @brief Service pack or major update if present
        std::string service_pack() const;

        /// @brief Windows edition, like "Home Premium" or "Professional"
        /// Specific editions should comply with the system version, for example
        /// "Windows 7 Professional N", "Windows 10 Education"
        std::string edition() const;

        /// @brief ProductName is Windows version and edition with spaces, 
        /// "Windows 7 Professional N"
        std::string product_name() const;

        /// @brief "Client" or "Server"
        std::string installation_type() const;

        /// @brief Unix time format, depend on the system release date, 
        /// since installation date can't be before release date
        int installation_date() const;

        /// @brief Full Windows build version
        /// For example, Windows 7 is "6.1.7600.16385", Windows 8.1 is "6.3.9600.17031"
        std::string build() const;

        /// @brief Build GUID, unique for every build number, random if no info
        std::string build_guid() const;

        /// @brief CSD Version, string representation of Service Pack or major update
        /// Example: "Service Pack 1"
        std::string csd_version() const;

        /// @brief CSDBuildNumber, numerical version of Service Pack or major update
        int csd_build_number() const;

        /// @brief BuildLab string representation
        /// Example: "7601.win7sp1_ldr.170913-0600"
        std::string build_lab() const;

        /// @brief BuildLabEx string representation
        /// Example: "7601.23915.amd64fre.win7sp1_ldr.170913-0600"
        std::string build_lab_ex() const;

        /// @brief String representation of system major.minor version
        /// Example: "6.1"
        std::string current_version() const;

        /// @brief String representation of CurrentBuild
        /// Example: "7600"
        std::string current_build() const;

        /// @brief Numeric representation of CurrentBuild
        /// Example: 7600
        int current_build_number() const;

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

    private:

        //////////////////////////////////////////////////////////////////////////
        // Static Data

        // System versions
        static std::vector<int> _system_versions;

        // System version to name
        static std::map<int, std::string> _system_version_name;

        //////////////////////////////////////////////////////////////////////////
        /// Generated Fingerprint

        /// From Windows 7 to Windows 10
        int _windows_version;

        /// OEM or Retail version
        bool _oem;

        /// Edition ID, which is base for many other params
        WindowsEditionSKU _edition;

        /// For example, Windows 7 is "6.1.7600.16385", Windows 8.1 is "6.3.9600.17031"
        WindowsBuild _windows_build;

        /// Unix time format, depend on the system release date
        int _install_date;

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
