#pragma once
#include <winfp/fingerprint_data_base.h>

#include <string>
#include <vector>
#include <map>
#include <cstdint>


namespace antios {


class WindowsFingerprintData
{
public:

    /// @brief Windows product version without Service Packs and major updates
    enum class ProductName
    {
        Windows7,
        Windows8,
        Windows81,
        Windows10,
        // This is count of all enum items
        ProductNameCount
    };

    /// @brief Windows version including Service Packs and major updates
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

    /// @brief all possible Windows editions
    /// See all editions specific for particular system below:
    /// Windows 7 SKU
    /// {Enterprise, EnterpriseE, EnterpriseK, EnterpriseKN, EnterpriseN,
    ///  HomeBasic, HomeBasicE, HomeBasicK, HomeBasicKN, HomeBasicN,
    ///  HomePremium, HomePremiumE, HomePremiumK, HomePremiumKN
    ///  Professional, ProfessionalE, ProfessionalK, ProfessionalKN, ProfessionalN
    ///  Starter, StarterE, StarterK, StarterKN, StarterN,
    ///  Ultimate, UltimateE, UltimateK, UltimateKN, UltimateN}
    /// Windows 8 SKU (Media Center editions excluded until beta)
    /// {Core, CoreK, CoreKN, CoreN
    ///  Enterprise, EnterpriseK, EnterpriseKN, EnterpriseN
    ///  Pro, ProK, ProKMediaCenter, ProKN, ProN, ProMediaCenter}
    /// Windows 8.1 SKU (Media Center and Country Specific editions excluded)
    /// {Core, CoreConnected, CoreN,
    ///  CoreConnectedCountrySpecific, CoreConnectedSingleLanguage, 
    ///  Enterprise, 
    /// Pro, ProEducation, ProK, ProMediaCenter}
    /// Windows 10 SKU (IoT Editions have specific since they intended to run embedded hardware)
    /// {Education, EducationN
    ///  Enterprise, EnterpriseLTSB
    ///  Home, HomeN
    ///  Pro, ProN,
    ///  IoTCore, IoTEnterprise, S}
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

    struct ProductInfo
    {
        std::string product_name;
        ProductName product_name_id;
    };

    struct SubproductInfo
    {
        std::string subproduct_name;
        SubproductName subproduct_name_id;
    };

    /// @brief Information about edition
    /// ID for internal representation, name for registry (usually without spaces)
    /// and human-readable name
    struct EditionInfo
    {
        std::string registry_name;
        std::string readable_name;
    };

    /// @brief Build information stored in CurrentVersion registry key
    /// Represent one particular build and should not be inconsistent
    /// (Windows 10 can't be installed in 2009, Windows 7 NT version is 6.1 only etc)
    struct WindowsBuildInfo
    {
        /// Enum for filtering by product name
        ProductName product_name_id;

        /// Enum for filtering by product major update
        SubproductName subproduct_name_id;

        /// Example: "Windows 10"
        std::string product_version;

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

        /// Release date (because of lack of exact date often refers to the last day of release month)
        int release_date{};

        /// System-specific values
        std::map<std::string, std::string> system_specific;
    };

    /// @brief Default
    WindowsFingerprintData() = default;

    /// @brief Destructor is not polymorph, because class is not intended to participate in inheritance
    ~WindowsFingerprintData() = default;

    /// @brief Create a "query" to all possible builds based on user selection
    /// For example, all builds Windows 7 SP1 builds, all Windows 10 1803 builds
    static std::vector<WindowsBuildInfo> build_by_product(WindowsFingerprintData::ProductName product_name);

    /// @brief Create a "query" to all possible builds based on user selection
    /// For example, all builds Windows 7 SP1 builds, all Windows 10 1803 builds
    static std::vector<WindowsBuildInfo> build_by_subproduct(WindowsFingerprintData::SubproductName subproduct_name);

    /// @brief Create a "query" to all possible editions based on product version
    /// For example, all editions of Windows 7
    static std::map<WindowsEditionSKU, EditionInfo> editions_by_product(WindowsFingerprintData::ProductName product_name);

    /// @brief Create a "query" to all possible subproduct based on product version
    /// For example, "Windows 7" and "Windows 7 SP1" by Windows 7
    static std::vector<WindowsFingerprintData::SubproductName> subproducts_by_product(
        WindowsFingerprintData::ProductName product_name);

    /// @brief All products from Windows 7 to 10
    static std::vector<std::string> all_products();

    /// @brief All products from Windows 7 to 10 including service packs and updates
    static std::vector<std::string> all_supproducts();

    /// @brief Get ProductName ID for queries
    static WindowsFingerprintData::ProductInfo get_product(const std::string& product_name);

    /// @brief Get SubproductName ID for queries
    static WindowsFingerprintData::SubproductInfo get_subproduct(const std::string& subproduct_name);

    /// @brief Get ProductName ID for queries
    static WindowsFingerprintData::ProductInfo get_product(WindowsFingerprintData::ProductName product_name);

    /// @brief Get SubproductName ID for queries
    static WindowsFingerprintData::SubproductInfo get_subproduct(WindowsFingerprintData::SubproductName subproduct_name);

    /// @brief Windows edition, like "Home Premium" or "Professional"
    /// Specific editions should comply with the system version, for example
    /// "Windows 7 Professional N", "Windows 10 Education"
    static std::string get_edition(WindowsEditionSKU edition);

    /// @brief Registry value for EditionID key
    /// Registry value is almost the same as readable, just without spaces
    static std::string get_edition_id(WindowsEditionSKU edition);

    //////////////////////////////////////////////////////////////////////////
    // Build info

private:

    //////////////////////////////////////////////////////////////////////////
    // Static Data

    static std::vector<ProductInfo> _product_string;

    static std::vector<SubproductInfo> _subproduct_string;

    static std::map<ProductName, std::vector<SubproductName>> _products_to_subproducts;

    static std::map<WindowsEditionSKU, EditionInfo> _editions_info;

    static std::map<ProductName, std::vector<WindowsEditionSKU>> _version_editions;

    static std::vector<WindowsBuildInfo> _builds_information;
};

} // namespace antios 
