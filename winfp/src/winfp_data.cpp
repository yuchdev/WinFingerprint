#include <winfp/winfp_data.h>

#include <ctime>
#include <cassert>
#include <algorithm>

using namespace antios;

// static
std::map<std::string, WindowsFingerprint::ProductName> WindowsFingerprint::_product_string = {
    {std::make_pair("Windows 7", ProductName::Windows7)},
    {std::make_pair("Windows 8", ProductName::Windows8)},
    {std::make_pair("Windows 8.1", ProductName::Windows81)},
    {std::make_pair("Windows 10", ProductName::Windows10)}
};

// static
std::map<std::string, WindowsFingerprint::SubproductName> antios::WindowsFingerprint::_subproduct_string = {
    {std::make_pair("Windows 7", SubproductName::Windows7noUpdate)},
    {std::make_pair("Windows 7 SP1", SubproductName::Windows7SP1)},
    {std::make_pair("Windows 8", SubproductName::Windows8noUpdate)},
    {std::make_pair("Windows 8.1", SubproductName::Windows81noUpdate)},
    {std::make_pair("Windows 8.1 IR3", SubproductName::Windows81IR3Update)},
    {std::make_pair("Windows 8.1 IR4", SubproductName::Windows81IR4Update)},
    {std::make_pair("Windows 8.1 IR5", SubproductName::Windows81IR5Update)},
    {std::make_pair("Windows 10 1507", SubproductName::Windows10v1507)},
    {std::make_pair("Windows 10 1511", SubproductName::Windows10v1511)},
    {std::make_pair("Windows 10 1607", SubproductName::Windows10v1607)},
    {std::make_pair("Windows 10 1703", SubproductName::Windows10v1703)},
    {std::make_pair("Windows 10 1709", SubproductName::Windows10v1709)},
    {std::make_pair("Windows 10 1803", SubproductName::Windows10v1803)},
    {std::make_pair("Windows 10 1809", SubproductName::Windows10v1809)},
    {std::make_pair("Windows 10 1903", SubproductName::Windows10v1903)}
};

// static
std::map<WindowsFingerprint::ProductName, std::vector<WindowsFingerprint::SubproductName>> 
antios::WindowsFingerprint::_products_to_subproducts = {
    {std::make_pair(ProductName::Windows7, std::vector<WindowsFingerprint::SubproductName>{
        SubproductName::Windows7noUpdate,
        SubproductName::Windows7SP1}
    )},
    {std::make_pair(ProductName::Windows8, std::vector<WindowsFingerprint::SubproductName>{
        SubproductName::Windows8noUpdate}
    )},
    {std::make_pair(ProductName::Windows81, std::vector<WindowsFingerprint::SubproductName>{
        SubproductName::Windows81noUpdate, SubproductName::Windows81IR3Update, SubproductName::Windows81IR4Update, SubproductName::Windows81IR5Update}
    )},
    {std::make_pair(ProductName::Windows10, std::vector<WindowsFingerprint::SubproductName>{
        SubproductName::Windows10v1507, SubproductName::Windows10v1511, SubproductName::Windows10v1607, SubproductName::Windows10v1703,
        SubproductName::Windows10v1709, SubproductName::Windows10v1803, SubproductName::Windows10v1809, SubproductName::Windows10v1903 }
    )}
};

// static
std::map<WindowsFingerprint::WindowsEditionSKU, WindowsFingerprint::EditionInfo> WindowsFingerprint::_editions_info = {
    {std::make_pair(Starter, EditionInfo{"Starter", "Starter"})},
    {std::make_pair(StarterE, EditionInfo{"StarterE", "Starter E"})},
    {std::make_pair(StarterK, EditionInfo{"StarterK","Starter K"})},
    {std::make_pair(StarterKN, EditionInfo{"StarterKN", "Starter KN"})},
    {std::make_pair(StarterN, EditionInfo{"StarterN", "Starter N"})},
    {std::make_pair(HomeBasic, EditionInfo{"HomeBasic", "Home Basic"})},
    {std::make_pair(HomeBasicE, EditionInfo{"HomeBasicE", "HomeBasic E"})},
    {std::make_pair(HomeBasicK, EditionInfo{"HomeBasicK", "Home Basic K"})},
    {std::make_pair(HomeBasicKN, EditionInfo{"HomeBasicKN","Home Basic KN"})},
    {std::make_pair(HomeBasicN, EditionInfo{"HomeBasicN", "Home Basic N"})},
    {std::make_pair(HomePremium, EditionInfo{"HomePremium","Home Premium"})},
    {std::make_pair(HomePremiumE, EditionInfo{"HomePremiumE","Home Premium E"})},
    {std::make_pair(HomePremiumK, EditionInfo{"HomePremiumK","Home Premium K"})},
    {std::make_pair(HomePremiumKN, EditionInfo{"HomePremiumKN", "Home Premium KN"})},
    {std::make_pair(Professional, EditionInfo{"Professional", "Professional"})},
    {std::make_pair(ProfessionalE, EditionInfo{"ProfessionalE", "Professional E"})},
    {std::make_pair(ProfessionalK, EditionInfo{"ProfessionalK", "Professional K"})},
    {std::make_pair(ProfessionalKN, EditionInfo{"ProfessionalKN", "Professional KN"})},
    {std::make_pair(ProfessionalN, EditionInfo{"ProfessionalN", "Professional N"})},
    {std::make_pair(Enterprise, EditionInfo{"Enterprise", "Enterprise"})},
    {std::make_pair(EnterpriseE, EditionInfo{"EnterpriseE", "Enterprise E"})},
    {std::make_pair(EnterpriseK, EditionInfo{"EnterpriseK", "Enterprise K"})},
    {std::make_pair(EnterpriseKN, EditionInfo{"EnterpriseKN", "Enterprise KN"})},
    {std::make_pair(EnterpriseN, EditionInfo{"EnterpriseN", "Enterprise N"})},
    {std::make_pair(Ultimate, EditionInfo{"Ultimate", "Ultimate"})},
    {std::make_pair(UltimateE, EditionInfo{"UltimateE", "UltimatE"})},
    {std::make_pair(UltimateK, EditionInfo{"UltimateK", "Ultimate K"})},
    {std::make_pair(UltimateKN, EditionInfo{"UltimateKN", "Ultimate KN"})},
    {std::make_pair(UltimateN, EditionInfo{"UltimateN", "Ultimate N"})},
    {std::make_pair(Core, EditionInfo{"Core", "Core"})},
    {std::make_pair(CoreK, EditionInfo{"CoreK", "Core K"})},
    {std::make_pair(CoreKN, EditionInfo{"CoreKN", "Core KN"})},
    {std::make_pair(CoreN, EditionInfo{"CoreN", "Core N"})},
    {std::make_pair(CoreConnected, EditionInfo{"CoreConnected", "Core Connected"})},
    {std::make_pair(ProEducation, EditionInfo{"ProEducation", "Pro Education"})},
    {std::make_pair(Pro, EditionInfo{"Pro", "Pro"})},
    {std::make_pair(ProK, EditionInfo{"ProK", "Pro K"})},
    {std::make_pair(ProKN, EditionInfo{"ProKN", "Pro KN"})},
    {std::make_pair(ProN, EditionInfo{"ProN", "Pro N"})},
    {std::make_pair(Education, EditionInfo{"Education", "Education"})},
    {std::make_pair(EducationN, EditionInfo{"EducationN", "Education N"})},
    {std::make_pair(EnterpriseLTSB, EditionInfo{"EnterpriseLTSB", "Enterprise LTSB"})},
    {std::make_pair(Home, EditionInfo{"Home", "Home"})},
    {std::make_pair(HomeN, EditionInfo{"HomeN", "Home N"})},
    {std::make_pair(S, EditionInfo{"S", "S"})}
};

// static
std::map<WindowsFingerprint::ProductName, std::vector<WindowsFingerprint::WindowsEditionSKU>> 
WindowsFingerprint::_version_editions = {
    
    // Windows 7
    {std::make_pair(ProductName::Windows7, std::vector<WindowsFingerprint::WindowsEditionSKU> {
        Enterprise, EnterpriseE, EnterpriseK, EnterpriseKN, EnterpriseN,
        HomeBasic, HomeBasicE, HomeBasicK, HomeBasicKN, HomeBasicN,
        HomePremium, HomePremiumE, HomePremiumK, HomePremiumKN,
        Professional, ProfessionalE, ProfessionalK, ProfessionalKN, ProfessionalN,
        Starter, StarterE, StarterK, StarterKN, StarterN,
        Ultimate, UltimateE, UltimateK, UltimateKN, UltimateN
        }),
    },

    // Windows 8
    {std::make_pair(ProductName::Windows7, std::vector<WindowsEditionSKU> {
        Core, CoreK, CoreKN, CoreN,
        Enterprise, EnterpriseK, EnterpriseKN, EnterpriseN,
        Pro, ProK, ProKN, ProN
        }),
    },

    // Windows 8.1
    {std::make_pair(ProductName::Windows7, std::vector<WindowsEditionSKU> {
        Core, CoreConnected, CoreN,
        Enterprise,
        Pro, ProEducation, ProK
        }),
    },

    // Windows 10
    {std::make_pair(ProductName::Windows7, std::vector<WindowsEditionSKU>  {
        Education, EducationN,
        Enterprise, EnterpriseLTSB,
        Home, HomeN,
        Pro, ProN, S
        })
    }
};

// static
std::vector<WindowsFingerprint::WindowsBuildInfo> WindowsFingerprint::_builds_information = {

// Windows 7, 6.1.7600.16385, October 2009
WindowsBuildInfo{
    ProductName::Windows7,
    SubproductName::Windows7noUpdate,
    "Windows 7", 
    "6.1", 
    "7600", 
    "6.1.7600.16385", 
    "7600.win7_rtm.090713-1255", 
    "7600.16385.win7_rtm.090713-1255", 
    1256212800,
    {}
},

// Windows 7 SP 1, 6.1.7601.16385, November 2010
WindowsBuildInfo{
    ProductName::Windows7,
    SubproductName::Windows7SP1,
    "Windows 7",
    "6.1",
    "7601",
    "6.1.7601.16385",
    "7601.win7_rtm.090713-1255",
    "7601.16385.win7_rtm.090713-1255",
    1291118400,
    {std::make_pair("CSDVersion", "Service Pack 1"), std::make_pair("CSDBuildNumber", "1130")}
},

// Windows 7 SP 1, 6.1.7601.16385, 22 February 2011
WindowsBuildInfo{
    ProductName::Windows7,
    SubproductName::Windows7SP1,
    "Windows 7",
    "6.1",
    "7601",
    "6.1.7601.17514",
    "7601.win7sp1_rtm.101119-1850",
    "7601.16385.win7sp1_rtm.101119-1850",
    1256212800,
    {std::make_pair("CSDVersion", "Service Pack 1"), std::make_pair("CSDBuildNumber", "1130")}
},


// Windows 7 SP 1, 6.1.7601.17514, available for Ultimate, Professional, Home Premium and x64 only
WindowsBuildInfo{
    ProductName::Windows7,
    SubproductName::Windows7SP1,
    "Windows 7",
    "6.1",
    "7601",
    "6.1.7601.24214",
    "7601.win7sp1_ldr_escrow.180801-1700",
    "7601.24214.win7sp1_ldr_escrow.180801-1700",
    1256212800,
    {std::make_pair("CSDVersion", "Service Pack 1"), std::make_pair("CSDBuildNumber", "1130")}
},


    // Windows 8: 6.2.9200.16384, October 2010
WindowsBuildInfo{
    ProductName::Windows8,
    SubproductName::Windows8noUpdate,
    "Windows 8",
    "6.2",
    "9200",
    "6.2.9200.16384",
    "9200.16384.win8_rtm.120725-1247",
    "9200.16384.win8_rtm.120725-1247",
    1351598400,
    {}
},


// Windows 8.1: 6.3.9600.16384, 8 April 2013
WindowsBuildInfo{
    ProductName::Windows81,
    SubproductName::Windows81noUpdate,
    "Windows 8.1",
    "6.3",
    "9600",
    "6.3.9600.16384",
    "9600.winblue_rtm.130821-1623",
    "9600.16384.winblue_rtm.130821-1623",
    1365422400,
    {}
},


// Windows 8.1 IR3: 6.3.9600.17031, release date unknown, set to January 2014
WindowsBuildInfo{
    ProductName::Windows81,
    SubproductName::Windows81IR3Update,
    "Windows 8.1",
    "6.3",
    "9600",
    "6.3.9600.17031",
    "9600.winblue_gdr.140221-1952",
    "9600.17031.winblue_gdr.140221-1952",
    1389182400,
    {}
},


// Windows 8.1 IR4: 6.3.9600.17238, release date unknown, set to April 2014
WindowsBuildInfo{
    ProductName::Windows81,
    SubproductName::Windows81IR4Update,
    "Windows 8.1",
    "6.3",
    "9600",
    "6.3.9600.17238",
    "9600.winblue_gdr.140723-2018",
    "9600.17238.winblue_gdr.140723-2018",
    1396958400,
    {}
},


// Windows 8.1 IR5: 6.3.9600.17415, November 2014
WindowsBuildInfo{
    ProductName::Windows81,
    SubproductName::Windows81IR5Update,
    "Windows 8.1",
    "6.3",
    "9600",
    "6.3.9600.17415",
    "9600.winblue_gdr.140723-2018",
    "9600.17415.winblue_gdr.140723-2018",
    1417348800,
    {}
},


// Windows 10 1507, 10.0.10176.16384, July 2015
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1507,
    "Windows 10",
    "10.0",
    "10176",
    "10.0.10176.16384",
    "10176.th1.150705-1526",
    "10176.16384.th1.150705-1526",
    1438257600,
    {}
},


// Windows 10 1507, 10.0.10240.16425, release date unknown, set to August 2015
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1507,
    "Windows 10",
    "10.0",
    "10240",
    "10.0.10240.16425",
    "10240.th1.150802-1600",
    "10240.16425.th1.150802-1600",
    1440936000,
    {}
},


// Windows 10 1507, 10.0.10240.16487, release date unknown, set to May 2015
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1507,
    "Windows 10",
    "10.0",
    "10240",
    "10.0.10240.16487",
    "10240.th1.150901-1507",
    "10240.16487.th1.150901-1507",
    1432987200,
    {std::make_pair("ReleaseId", "1507")}
},


// Windows 10 1511, 10.0.10586.104, March 2016
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1511,
    "Windows 10",
    "10.0",
    "10586",
    "10.0.10586.104",
    "10586.th2_release.160128-1934",
    "10586.104.th2_release.160128-1934",
    1459339200,
    {std::make_pair("ReleaseId", "1511")}
},


// Windows 10 1511, 10.0.10586.164, May 2016
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1511,
    "Windows 10",
    "10.0",
    "10586",
    "10.0.10586.164",
    "10586.th2_release.160229-1806",
    "10586.164.th2_release.160229-1806",
    1464609600,
    {std::make_pair("ReleaseId", "1511")}
},


// Windows 10 1511, 10.0.10587.0, November 2016, Home and Pro only
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1511,
    "Windows 10",
    "10.0",
    "10587",
    "10.0.10587.0",
    "10587.th2.151111-1718",
    "10587.0.th2.151111-1718",
    1480507200,
    {std::make_pair("ReleaseId", "1511")}
},


// Windows 10 1607, 10.0.14393.0, August 2016
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1607,
    "Windows 10",
    "10.0",
    "14393",
    "10.0.14393.0",
    "14393.rs1_release.160715-1616",
    "14393.0.rs1_release.160715-1616",
    1472558400,
    {std::make_pair("ReleaseId", "1607")}
},


// Windows 10 1607, 10.0.14393.447, release date unknown, set to October 2016
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1607,
    "Windows 10",
    "10.0",
    "14393",
    "10.0.14393.447",
    "14393.rs1_release.160715-1616",
    "14393.447.rs1_release.160715-1616",
    1477828800,
    {std::make_pair("ReleaseId", "1607")}
},


// Windows 10 1703, 10.0.15063.0, April 2017
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1703,
    "Windows 10",
    "10.0",
    "15063",
    "10.0.15063.0",
    "15063.rs2_release.170317-1834",
    "15063.0.rs2_release.170317-1834",
    1493553600,
    {std::make_pair("ReleaseId", "1703")}
},


// Windows 10 1703, 10.0.15063.2, July 2017
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1703,
    "Windows 10",
    "10.0",
    "15063",
    "10.0.15063.2",
    "15063.rs2_release_svc_d.170531-1743",
    "15063.2.rs2_release_svc_d.170531-1743",
    1501416000,
    {std::make_pair("ReleaseId", "1703")}
},


// Windows 10 1703, 10.0.15063.413, release date unknown, set to November 2017
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1703,
    "Windows 10",
    "10.0",
    "15063",
    "10.0.15063.413",
    "15063.rs2_release_svc_escrow.170602-2301",
    "15063.413.rs2_release_svc_escrow.170602-2301",
    1512043200,
    {std::make_pair("ReleaseId", "1703")}
},


// Windows 10 1703, 10.0.15063.483, release date unknown, set to March 2018
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1703,
    "Windows 10",
    "10.0",
    "15063",
    "10.0.15063.483",
    "15063.rs2_release_svc_escrow.170706-2006",
    "15063.483.rs2_release_svc_escrow.170706-2006",
    1522411200,
    {std::make_pair("ReleaseId", "1703")}
},


// Windows 10 1709, 10.0.16299.15, October 2017
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1709,
    "Windows 10",
    "10.0",
    "16299",
    "10.0.16299.15",
    "16299.rs3_release.170928-1534",
    "16299.15.rs3_release.170928-1534",
    1509364800,
    {std::make_pair("ReleaseId", "1709")}
},


// Windows 10 1709, 10.0.16299.64, November 2017
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1709,
    "Windows 10",
    "10.0",
    "16299",
    "10.0.16299.64",
    "16299.rs3_release_svc.171024-1647",
    "16299.64.rs3_release_svc.171024-1647",
    1512043200,
    {std::make_pair("ReleaseId", "1709")}
},


// Windows 10 1709, 10.0.16299.125, December 2017 
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1709,
    "Windows 10",
    "10.0",
    "16299",
    "10.0.16299.125",
    "16299.rs3_release_svc_escrow.171207-1044",
    "16299.125.rs3_release_svc_escrow.171207-1044",
    1514635200,
    {std::make_pair("ReleaseId", "1709")}
},


// Windows 10 1803, 10.0.17134.1, April 2018
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.1",
    "17134.rs4_release.180410-1804",
    "17134.1.rs4_release.180410-1804",
    1525089600,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.112, July 2018
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.112",
    "17134.rs4_release_svc_prod1.180607-2257",
    "17134.112.rs4_release_svc_prod1.180607-2257",
    1532952000,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.228, August 2018
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.228",
    "17134.rs4_release_svc_prod1.180802-1721",
    "17134.228.rs4_release_svc_prod1.180802-1721",
    1535630400,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.285, September 2018
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.285",
    "17134.rs4_release_svc_prod1.180830-1731",
    "17134.285.rs4_release_svc_prod1.180830-1731",
    1538308800,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.523, January 2019
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.523",
    "17134.rs4_release_svc_prod1.181231-1749",
    "17134.523.rs4_release_svc_prod1.181231-1749",
    1548849600,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.706, April 2019
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.706",
    "17134.rs4_release_svc_prod1.190401-1813",
    "17134.706.rs4_release_svc_prod1.190401-1813",
    1556625600,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.766, May 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.766",
    "17134.rs4_release_svc_im.190516-1931",
    "17134.766.rs4_release_svc_im.190516-1931",
    1559217600,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.829, June 2019
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.829",
    "17134.rs4_release_svc_prod1.190606-1933",
    "17134.829.rs4_release_svc_prod1.190606-1933",
    1561896000,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1803, 10.0.17134.885, July 2019
WindowsBuildInfo{
    ProductName::Windows10,
    SubproductName::Windows10v1803,
    "Windows 10",
    "10.0",
    "17134",
    "10.0.17134.885",
    "17134.rs4_release_svc_prod1.190703-1836",
    "17134.885.rs4_release_svc_prod1.190703-1836",
    1563192000,
    {std::make_pair("ReleaseId", "1803")}
},


// Windows 10 1809, 10.0.17763.1, October 2018
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.1",
    "17763.rs5_release.180914-1434",
    "17763.1.rs5_release.180914-1434",
    1538481600,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.107, November 2018
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.107",
    "17763.rs5_release_svc_prod2.181026-1406",
    "17763.107.rs5_release_svc_prod2.181026-1406",
    1543579200,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.194, December 2018
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.194",
    "17763.rs5_release_svc_prod1.181203-1758",
    "17763.194.rs5_release_svc_prod1.181203-1758",
    1546171200,
    {std::make_pair("ReleaseId", "1809")}
},

    
// Windows 10 1809, 10.0.17763.253, January 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.253",
    "17763.rs5_release_svc_prod1.181231-1749",
    "17763.253.rs5_release_svc_prod1.181231-1749",
    1517313600,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.316, February 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.316",
    "17763.rs5_release_svc_prod1.190205-1455",
    "17763.316.rs5_release_svc_prod1.190205-1455",
    1519992000,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.379, March 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.379",
    "17763.rs5_release_svc_prod1.190306-1916",
    "17763.379.rs5_release_svc_prod1.190306-1916",
    1522411200,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.437, April 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.437",
    "17763.rs5_release_svc_im.190401-1813",
    "17763.437.rs5_release_svc_im.190401-1813",
    1525089600,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.504, May 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.504",
    "17763.rs5_release_svc_im.190516-1930",
    "17763.504.rs5_release_svc_im.190516-1930",
    1527681600,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1809, 10.0.17763.557, June 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.557",
    "17763.rs5_release_svc_prod1.190606-1817",
    "17763.557.rs5_release_svc_prod1.190606-1817",
    1561896000,
    {std::make_pair("ReleaseId", "1809")}
},

    
// Windows 10 1809, 10.0.17763.615, July 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1809,
    "Windows 10",
    "10.0",
    "17763",
    "10.0.17763.615",
    "17763.rs5_release_svc_prod1.190630-1301",
    "17763.615.rs5_release_svc_prod1.190630-1301",
    1531656000,
    {std::make_pair("ReleaseId", "1809")}
},


// Windows 10 1903, 10.0.18362.30, May 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1903,
    "Windows 10",
    "10.0",
    "18362",
    "10.0.18362.30",
    "18362.19h1_release_svc_prod2.190329-2159",
    "18362.30.19h1_release_svc_prod2.190329-2159",
    1527681600,
    {std::make_pair("ReleaseId", "1903")}
},


// Windows 10 1903, 10.0.18362.175, June 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1903,
    "Windows 10",
    "10.0",
    "18362",
    "10.0.18362.175",
    "18362.19h1_release_svc_prod1.190606-1842",
    "18362.175.19h1_release_svc_prod1.190606-1842",
    1561896000,
    {std::make_pair("ReleaseId", "1903")}
},


// Windows 10 1903, 10.0.18362.239, July 2019
WindowsBuildInfo{ 
    ProductName::Windows10,
    SubproductName::Windows10v1903,
    "Windows 10",
    "10.0",
    "18362",
    "10.0.18362.239",
    "18362.19h1_release_svc_prod1.190628-1641",
    "18362.239.19h1_release_svc_prod1.190628-1641",
    1531656000,
    {std::make_pair("ReleaseId", "1903")}
}

}; // end of WindowsFingerprint::_builds_information


WindowsFingerprint::WindowsFingerprint()
{
}

void WindowsFingerprint::generate_product_id()
{
    std::string alphabet{"0123456789"};
    std::string ret{23};
    ret = random_string(5, alphabet);
    ret += '-';
    ret += _oem ? "OEM" : random_string(3, alphabet);
    ret += '-';
    ret += random_string(7, alphabet);
    ret += '-';
    ret += random_string(5, alphabet);
    _product_id.swap(ret);
}

void WindowsFingerprint::generate()
{
    std::vector<bool> oem{ true, false };
    
    // OEM/Retail
    _oem = this->choise(oem);

    // Random build
    _build_info = this->choise(_builds_information);

    // Edition based on random build
    std::map<WindowsEditionSKU, EditionInfo>& available_editions = editions_by_product(_build_info.product_name_id);
    _edition = this->choise(available_editions).first;
    
    // Install date based on Windows version release date
    _install_date = this->random_from_range(_build_info.release_date, std::time(nullptr));

    // ProductID
    generate_product_id();
}


std::vector<WindowsFingerprint::WindowsBuildInfo> WindowsFingerprint::build_by_product(
    WindowsFingerprint::ProductName product_name) const
{
    std::vector<WindowsFingerprint::WindowsBuildInfo> ret;
    std::copy_if(std::begin(_builds_information), std::end(_builds_information), 
        std::back_inserter(ret),
        [product_name](const WindowsFingerprint::WindowsBuildInfo& b) { 
        return b.product_name_id == product_name; 
    });
    return std::move(ret);
}

std::vector<WindowsFingerprint::WindowsBuildInfo> WindowsFingerprint::build_by_subproduct(
    WindowsFingerprint::SubproductName subproduct_name) const
{
    std::vector<WindowsFingerprint::WindowsBuildInfo> ret;
    std::copy_if(std::begin(_builds_information), std::end(_builds_information),
        std::back_inserter(ret),
        [subproduct_name](const WindowsFingerprint::WindowsBuildInfo& b) {
        return b.subproduct_name_id == subproduct_name;
    });
    return std::move(ret);
}

std::map<WindowsFingerprint::WindowsEditionSKU, WindowsFingerprint::EditionInfo> antios::WindowsFingerprint::editions_by_product(WindowsFingerprint::ProductName product_name) const
{
    std::map<WindowsFingerprint::WindowsEditionSKU, WindowsFingerprint::EditionInfo> ret;
    auto editions_iter = _version_editions.find(product_name);
    assert(editions_iter != _version_editions.end());
    std::vector<WindowsFingerprint::WindowsEditionSKU> available_editions = editions_iter->second;
    // filter all available edition
    for (const auto& edition : available_editions) {
        ret[edition] = _editions_info[edition];
    }
    return std::move(ret);
}

std::vector<WindowsFingerprint::SubproductName> WindowsFingerprint::subproducts_by_product(
    WindowsFingerprint::ProductName product_name) const
{
    auto product_iter = _products_to_subproducts.find(product_name);
    assert(product_iter != _products_to_subproducts.end());
    return (*product_iter).second;
}

std::vector<std::string> WindowsFingerprint::all_products() const
{
    std::vector<std::string> all_windows;
    all_windows.reserve(_product_string.size());
    for (auto const& prod : _product_string)
        all_windows.push_back(prod.first);
    return std::move(all_windows);
}

std::vector<std::string> WindowsFingerprint::all_supproducts() const
{
    std::vector<std::string> all_windows;
    all_windows.reserve(_subproduct_string.size());
    for (auto const& prod : _subproduct_string)
        all_windows.push_back(prod.first);
    return std::move(all_windows);
}

std::string WindowsFingerprint::retail_oem() const
{
    return _oem ? "OEM" : "Retail";
}

std::string WindowsFingerprint::get_product_version() const
{
    return _build_info.product_version;
}

std::string WindowsFingerprint::get_nt_version() const
{
    return _build_info.nt_version;
}

std::string WindowsFingerprint::get_edition_id() const
{
    auto edition_iter = _editions_info.find(_edition);
    assert(edition_iter != _editions_info.end());
    return (*edition_iter).second.registry_name;
}

std::string WindowsFingerprint::get_edition() const
{
    auto edition_iter = _editions_info.find(_edition);
    assert(edition_iter != _editions_info.end());
    return (*edition_iter).second.readable_name;
}

std::string WindowsFingerprint::get_product_name() const
{
    std::string ret = _build_info.product_version;
    ret += ' ';
    ret += get_edition();
    return std::move(ret);
}

std::string WindowsFingerprint::get_short_version() const
{
    return _build_info.short_version;
}

std::string WindowsFingerprint::get_full_version() const
{
    return _build_info.full_version;
}

std::string WindowsFingerprint::get_build_lab() const
{
    return _build_info.build_lab;
}

std::string WindowsFingerprint::get_build_lab_ex() const
{
    return _build_info.build_lab_ex;
}

int WindowsFingerprint::get_installation_date() const
{
    return _install_date;
}

std::string antios::WindowsFingerprint::get_product_id() const
{
    return _product_id;
}

const std::map<std::string, std::string>& WindowsFingerprint::get_system_specific() const
{
    return _build_info.system_specific;
}

std::string WindowsFingerprint::get_build_guid() const
{
    throw std::logic_error("Not implemented");
    return std::string{};
}

std::vector<uint8_t> WindowsFingerprint::digital_product_id() const
{
    throw std::logic_error{ "Not implemented" };
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> WindowsFingerprint::digital_product_id4() const
{
    throw std::logic_error{ "Not implemented" };
    return std::vector<uint8_t>{};
}

std::vector<uint8_t> WindowsFingerprint::ie_install_date() const
{
    throw std::logic_error{ "Not implemented" };
    return std::vector<uint8_t>{};
}

std::string WindowsFingerprint::ie_service_update() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}
