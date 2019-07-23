﻿#pragma once
#include <winfp/fingerprint_data_base.h>

#include <boost/bimap.hpp>

#include <string>
#include <vector>
#include <map>
#include <cstdint>


namespace antios {


class WindowsFingerprint : public antios::FingerprintDataBase
{
public:

    enum class ProductName
    {
        Windows7,
        Windows8,
        Windows81,
        Windows10,
        // This is count of all enum items
        ProductNameCount
    };

    enum class SubproductName
    {
        Windows7noUpdate,
        Windows7SP1,
        Windows8noUpdate,
        Windows81noUpdate,
        Windows81IR3Update,
        Windows81IR4Update,
        Windows81IR5Update,
        Windows10v1507,
        Windows10v1511,
        Windows10v1607,
        Windows10v1703,
        Windows10v1709,
        Windows10v1803,
        Windows10v1809,
        Windows10v1903,
        // This is count of all enum items
        ProductNameCount
    };

    // Windows 7 SKU
    // {Enterprise, EnterpriseE, EnterpriseK, EnterpriseKN, EnterpriseN,
    //  HomeBasic, HomeBasicE, HomeBasicK, HomeBasicKN, HomeBasicN,
    //  HomePremium, HomePremiumE, HomePremiumK, HomePremiumKN
    //  Professional, ProfessionalE, ProfessionalK, ProfessionalKN, ProfessionalN
    //  Starter, StarterE, StarterK, StarterKN, StarterN,
    //  Ultimate, UltimateE, UltimateK, UltimateKN, UltimateN}

    // Windows 8 SKU (Media Center editions excluded until beta)
    // {Core, CoreK, CoreKN, CoreN
    //  Enterprise, EnterpriseK, EnterpriseKN, EnterpriseN
    //  Pro, ProK, ProKMediaCenter, ProKN, ProN, ProMediaCenter}

    // Windows 8.1 SKU (Media Center and Country Specific editions excluded)
    // {Core, CoreConnected, CoreN,
    //  CoreConnectedCountrySpecific, CoreConnectedSingleLanguage, 
    //  Enterprise, 
    // Pro, ProEducation, ProK, ProMediaCenter}

    // Windows 10 SKU (IoT Editions have specific since they intended to run embedded hardware)
    // {Education, EducationN
    //  Enterprise, EnterpriseLTSB
    //  Home, HomeN
    //  Pro, ProN,
    //  IoTCore, IoTEnterprise, S}
    enum WindowsEditionSKU
    {
        // Windows 7 and other versions
        //

        // Starter
        Starter, 
        StarterE, 
        StarterK, 
        StarterKN, 
        StarterN,
            
        // HomeBasic
        HomeBasic, 
        HomeBasicE, 
        HomeBasicK, 
        HomeBasicKN, 
        HomeBasicN,
            
        // HomePremium
        HomePremium, 
        HomePremiumE, 
        HomePremiumK, 
        HomePremiumKN,
            
        // Professional
        Professional, 
        ProfessionalE, 
        ProfessionalK, 
        ProfessionalKN, 
        ProfessionalN,
            
        // Enterprise
        Enterprise, 
        EnterpriseE, 
        EnterpriseK, 
        EnterpriseKN, 
        EnterpriseN,
            
        // Ultimate
        Ultimate, 
        UltimateE, 
        UltimateK, 
        UltimateKN, 
        UltimateN,

        // Windows 8 specific
        // All Enterprise versions listed above
        //

        // Core
        Core, 
        CoreK, 
        CoreKN, 
        CoreN, 
        CoreConnected,
        // Pro
        ProEducation, 
        Pro, 
        ProK, 
        ProKN, 
        ProN,

        // Windows 10 specific 
        //

        // Education
        Education, 
        EducationN,

        // Enterprise (just Enterprise listed above)
        EnterpriseLTSB,

        // Home
        Home, 
        HomeN, 

        // Secure
        S,
            
        // This is count of all enum items
        EditionsCount
    };


    struct EditionInfo
    {
        WindowsEditionSKU edition_id;
        std::string registry_name;
        std::string readable_name;
    };

    struct WindowsBuildInfo
    {
        /// Enum for filtering by product name
        WindowsFingerprint::ProductName product_name_id;

        /// Enum for filtering by product major update
        WindowsFingerprint::SubproductName update_name_id;

        /// Example: "Windows 10"
        std::string product_name;

        /// String representation of NT kernel version, example: "6.1"
        std::string nt_version;

        /// Short build number, example: Windows 10 v1709 is "16299"
        std::string short_version;

        /// Full build number, example: Windows 10 v1809 is "10.0.17763.557"
        std::string full_version;

        /// Full build name with tag
        std::string build_lab;

        /// Full extended build name with tag
        std::string build_lab_ex;

        /// Release date (because of lack of exact date often refer to the last day of release month)
        int release_date{};

        /// System-specific values
        std::map<std::string, std::string> system_specific;
    };

    /// @brief Default
    WindowsFingerprint();

    /// @brief Make it polymorph
    virtual ~WindowsFingerprint() = default;

    /// @brief
    virtual void generate() override;

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

protected:

    static void static_init();

private:

    //////////////////////////////////////////////////////////////////////////
    // Static Data

    using ProductNameBimap = boost::bimap<std::string, ProductName>;

    using SubproductNameBimap = boost::bimap<std::string, SubproductName>;

    static bool _init;

    static ProductNameBimap _product_string;

    static SubproductNameBimap _subproduct_string;

    static std::vector<EditionInfo> _editions_info;

    static std::map<ProductName, std::vector<WindowsEditionSKU>> _version_editions;

    static std::vector<WindowsBuildInfo> _builds_information;

    //////////////////////////////////////////////////////////////////////////
    /// Generated Fingerprint

    /// OEM or Retail version
    bool _oem;

    /// Product name - Windows 7, Windows 8, Windows 8.1...
    ProductName _product_name = ProductName::ProductNameCount;

    /// Edition ID, which is base for many other params
    WindowsEditionSKU _edition = WindowsEditionSKU::EditionsCount;

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
