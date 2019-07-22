#include <winfp/winfp_data.h>

using namespace antios;

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
std::vector<antios::WindowsBuildInfo> WindowsFingerprint::_builds_information = {

// Windows 7, 6.1.7600.16385, October 2009
WindowsBuildInfo{
    "Windows 7", 
    "", 
    "6.1", 
    "7600", 
    "6.1.7600.16385", 
    "7600.win7_rtm.090713-1255", 
    "7600.16385.win7_rtm.090713-1255", 
    "", 
    1256212800
},

// Windows 7 SP 1, 6.1.7601.16385, November 2010
WindowsBuildInfo{
    "Windows 7",
    "Service Pack 1",
    "6.1",
    "7601",
    "6.1.7601.16385",
    "7601.win7_rtm.090713-1255",
    "7601.16385.win7_rtm.090713-1255",
    "1130",
    1291118400
},

// Windows 7 SP 1, 6.1.7601.16385, 22 February 2011
WindowsBuildInfo{
    "Windows 7",
    "Service Pack 1",
    "6.1",
    "7601",
    "6.1.7601.17514",
    "7601.win7sp1_rtm.101119-1850",
    "7601.16385.win7sp1_rtm.101119-1850",
    "1130",
    1256212800
},


// Windows 7 SP 1, 6.1.7601.17514, available for Ultimate, Professional, Home Premium and x64 only
WindowsBuildInfo{
    "Windows 7",
    "Service Pack 1",
    "6.1",
    "7601",
    "6.1.7601.24214",
    "7601.win7sp1_ldr_escrow.180801-1700",
    "7601.24214.win7sp1_ldr_escrow.180801-1700",
    "1130",
    1256212800
},


    // Windows 8: 6.2.9200.16384, October 2010
WindowsBuildInfo{
    "Windows 8",
    "",
    "6.2",
    "9200",
    "6.2.9200.16384",
    "9200.16384.win8_rtm.120725-1247",
    "9200.16384.win8_rtm.120725-1247",
    "",
    1351598400
},


// Windows 8.1: 6.3.9600.16384, 8 April 2013
WindowsBuildInfo{
    "Windows 8.1",
    "",
    "6.3",
    "9600",
    "6.3.9600.16384",
    "9600.winblue_rtm.130821-1623",
    "9600.16384.winblue_rtm.130821-1623",
    "",
    1365422400
},


// Windows 8.1 IR3: 6.3.9600.17031, release date unknown, set to January 2014
WindowsBuildInfo{
    "Windows 8.1",
    "IR3",
    "6.3",
    "9600",
    "6.3.9600.17031",
    "9600.winblue_gdr.140221-1952",
    "9600.17031.winblue_gdr.140221-1952",
    "",
    1389182400
},


// Windows 8.1 IR4: 6.3.9600.17238, release date unknown, set to April 2014
WindowsBuildInfo{
    "Windows 8.1",
    "IR4",
    "6.3",
    "9600",
    "6.3.9600.17238",
    "9600.winblue_gdr.140723-2018",
    "9600.17238.winblue_gdr.140723-2018",
    "",
    1396958400
},


// Windows 8.1 IR5: 6.3.9600.17415, November 2014
WindowsBuildInfo{
    "Windows 8.1",
    "IR5",
    "6.3",
    "9600",
    "6.3.9600.17415",
    "9600.winblue_gdr.140723-2018",
    "9600.17415.winblue_gdr.140723-2018",
    "",
    1417348800
},


// Windows 10 1507, 10.0.10176.16384, July 2015
WindowsBuildInfo{
    "Windows 10",
    "1507",
    "10.0",
    "10176",
    "10.0.10176.16384",
    "10176.th1.150705-1526",
    "10176.16384.th1.150705-1526",
    "",
    1438257600
},


// Windows 10 1507, 10.0.10240.16425, release date unknown, set to August 2015
WindowsBuildInfo{
    "Windows 10",
    "1507",
    "10.0",
    "10240",
    "10.0.10240.16425",
    "10240.th1.150802-1600",
    "10240.16425.th1.150802-1600",
    "",
    1440936000
},


// Windows 10 1507, 10.0.10240.16487, release date unknown, set to May 2015
WindowsBuildInfo{
    "Windows 10",
    "1507",
    "10.0",
    "10240",
    "10.0.10240.16487",
    "10240.th1.150901-1507",
    "10240.16487.th1.150901-1507",
    "",
    1432987200
},


// Windows 10 1511, 10.0.10586.104, March 2016
WindowsBuildInfo{
    "Windows 10",
    "1511",
    "10.0",
    "10586",
    "10.0.10586.104",
    "10586.th2_release.160128-1934",
    "10586.104.th2_release.160128-1934",
    "",
    1459339200
},


// Windows 10 1511, 10.0.10586.164, May 2016
WindowsBuildInfo{
    "Windows 10",
    "1511",
    "10.0",
    "10586",
    "10.0.10586.164",
    "10586.th2_release.160229-1806",
    "10586.164.th2_release.160229-1806",
    "",
    1464609600
},


// Windows 10 1511, 10.0.10587.0, November 2016, Home and Pro only
WindowsBuildInfo{
    "Windows 10",
    "1511",
    "10.0",
    "10587",
    "10.0.10587.0",
    "10587.th2.151111-1718",
    "10587.0.th2.151111-1718",
    "",
    1480507200
},


// Windows 10 1607, 10.0.14393.0, August 2016
WindowsBuildInfo{
    "Windows 10",
    "1607",
    "10.0",
    "14393",
    "10.0.14393.0",
    "14393.rs1_release.160715-1616",
    "14393.0.rs1_release.160715-1616",
    "",
    1472558400
},


// Windows 10 1607, 10.0.14393.447, release date unknown, set to October 2016
WindowsBuildInfo{
    "Windows 10",
    "1607",
    "10.0",
    "14393",
    "10.0.14393.447",
    "14393.rs1_release.160715-1616",
    "14393.447.rs1_release.160715-1616",
    "",
    1477828800
},


// Windows 10, 10.0.15063.0, 1703, April 2017
WindowsBuildInfo{
    "Windows 10",
    "1703",
    "10.0",
    "15063",
    "10.0.15063.0",
    "15063.rs2_release.170317-1834",
    "15063.0.rs2_release.170317-1834",
    "",
    1493553600
},


// Windows 10, 10.0.15063.2, 1703, July 2017
WindowsBuildInfo{"Windows 10",
    "1703",
    "10.0",
    "15063",
    "10.0.15063.2",
    "15063.rs2_release_svc_d.170531-1743",
    "15063.2.rs2_release_svc_d.170531-1743",
    "",
    1501416000
},


// Windows 10, 10.0.15063.413, 1703, release date unknown, set to November 2017
WindowsBuildInfo{
    "Windows 10",
    "1703",
    "10.0",
    "15063",
    "10.0.15063.413",
    "15063.rs2_release_svc_escrow.170602-2301",
    "15063.413.rs2_release_svc_escrow.170602-2301",
    "",
    1512043200
},


    // Windows 10, 10.0.15063.483, 1703, release date unknown, set to March 2018
WindowsBuildInfo{
    "Windows 10",
    "1703",
    "10.0",
    "15063",
    "10.0.15063.483",
    "15063.rs2_release_svc_escrow.170706-2006",
    "15063.483.rs2_release_svc_escrow.170706-2006",
    "",
    1522411200
},


// Windows 10 1709, 10.0.16299.15, October 2017
WindowsBuildInfo{
    "Windows 10",
    "1709",
    "10.0",
    "16299",
    "10.0.16299.15",
    "16299.rs3_release.170928-1534",
    "16299.15.rs3_release.170928-1534",
    "",
    1509364800
},


// Windows 10 1709, 10.0.16299.64, November 2017
WindowsBuildInfo{
    "Windows 10",
    "1709",
    "10.0",
    "16299",
    "10.0.16299.64",
    "16299.rs3_release_svc.171024-1647",
    "16299.64.rs3_release_svc.171024-1647",
    "",
    1512043200
},


// Windows 10 1709, 10.0.16299.125, December 2017 
WindowsBuildInfo{
    "Windows 10",
    "1709",
    "10.0",
    "16299",
    "10.0.16299.125",
    "16299.rs3_release_svc_escrow.171207-1044",
    "16299.125.rs3_release_svc_escrow.171207-1044",
    "",
    1514635200
},


// Windows 10 1803, 10.0.17134.1, April 2018
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.1",
    "17134.rs4_release.180410-1804",
    "17134.1.rs4_release.180410-1804",
    "",
    1525089600 
},


// Windows 10 1803, 10.0.17134.112, July 2018
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.112",
    "17134.rs4_release_svc_prod1.180607-2257",
    "17134.112.rs4_release_svc_prod1.180607-2257",
    "",
    1532952000
},


// Windows 10 1803, 10.0.17134.228, August 2018
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.228",
    "17134.rs4_release_svc_prod1.180802-1721",
    "17134.228.rs4_release_svc_prod1.180802-1721",
    "",
    1535630400
},


// Windows 10 1803, 10.0.17134.285, September 2018
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.285",
    "17134.rs4_release_svc_prod1.180830-1731",
    "17134.285.rs4_release_svc_prod1.180830-1731",
    "",
    1538308800 
},


// Windows 10 1803, 10.0.17134.523, January 2019
WindowsBuildInfo{ "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.523",
    "17134.rs4_release_svc_prod1.181231-1749",
    "17134.523.rs4_release_svc_prod1.181231-1749",
    "",
    1548849600 
},


// Windows 10 1803, 10.0.17134.706, April 2019
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.706",
    "17134.rs4_release_svc_prod1.190401-1813",
    "17134.706.rs4_release_svc_prod1.190401-1813",
    "",
    1556625600
},


// Windows 10 1803, 10.0.17134.766, May 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.766",
    "17134.rs4_release_svc_im.190516-1931",
    "17134.766.rs4_release_svc_im.190516-1931",
    "",
    1559217600 
},


// Windows 10 1803, 10.0.17134.829, June 2019
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.829",
    "17134.rs4_release_svc_prod1.190606-1933",
    "17134.829.rs4_release_svc_prod1.190606-1933",
    "",
    1561896000
},


// Windows 10 1803, 10.0.17134.885, July 2019
WindowsBuildInfo{
    "Windows 10",
    "1803",
    "10.0",
    "17134",
    "10.0.17134.885",
    "17134.rs4_release_svc_prod1.190703-1836",
    "17134.885.rs4_release_svc_prod1.190703-1836",
    "",
    1563192000 
},


// Windows 10 1809, 10.0.17763.1, October 2018
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.1",
    "17763.rs5_release.180914-1434",
    "17763.1.rs5_release.180914-1434",
    "",
    1538481600 
},


// Windows 10 1809, 10.0.17763.107, November 2018
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.107",
    "17763.rs5_release_svc_prod2.181026-1406",
    "17763.107.rs5_release_svc_prod2.181026-1406",
    "",
    1543579200
},


// Windows 10 1809, 10.0.17763.194, December 2018
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.194",
    "17763.rs5_release_svc_prod1.181203-1758",
    "17763.194.rs5_release_svc_prod1.181203-1758",
    "",
    1546171200 
},

    
// Windows 10 1809, 10.0.17763.253, January 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.253",
    "17763.rs5_release_svc_prod1.181231-1749",
    "17763.253.rs5_release_svc_prod1.181231-1749",
    "",
    1517313600 
},


// Windows 10 1809, 10.0.17763.316, February 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.316",
    "17763.rs5_release_svc_prod1.190205-1455",
    "17763.316.rs5_release_svc_prod1.190205-1455",
    "",
    1519992000
},


// Windows 10 1809, 10.0.17763.379, March 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.379",
    "17763.rs5_release_svc_prod1.190306-1916",
    "17763.379.rs5_release_svc_prod1.190306-1916",
    "",
    1522411200
},


// Windows 10 1809, 10.0.17763.437, April 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.437",
    "17763.rs5_release_svc_im.190401-1813",
    "17763.437.rs5_release_svc_im.190401-1813",
    "",
    1525089600 
},


// Windows 10 1809, 10.0.17763.504, May 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.504",
    "17763.rs5_release_svc_im.190516-1930",
    "17763.504.rs5_release_svc_im.190516-1930",
    "",
    1527681600
},


// Windows 10 1809, 10.0.17763.557, June 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1809",
    "10.0",
    "17763",
    "10.0.17763.557",
    "17763.rs5_release_svc_prod1.190606-1817",
    "17763.557.rs5_release_svc_prod1.190606-1817",
    "",
    1561896000 
},

    
// Windows 10 1809, 10.0.17763.615, July 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "17763",
    "10.0.17763.615",
    "17763.rs5_release_svc_prod1.190630-1301",
    "17763.615.rs5_release_svc_prod1.190630-1301",
    "",
    1531656000 
},


// Windows 10 1903, 10.0.18362.30, May 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "18362",
    "10.0.18362.30",
    "18362.19h1_release_svc_prod2.190329-2159",
    "18362.30.19h1_release_svc_prod2.190329-2159",
    "",
    1527681600
},


// Windows 10 1903, 10.0.18362.175, June 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "18362",
    "10.0.18362.175",
    "18362.19h1_release_svc_prod1.190606-1842",
    "18362.175.19h1_release_svc_prod1.190606-1842",
    "",
    1561896000
},


// Windows 10 1903, 10.0.18362.239, July 2019
WindowsBuildInfo{ 
    "Windows 10",
    "1903",
    "10.0",
    "18362",
    "10.0.18362.239",
    "18362.19h1_release_svc_prod1.190628-1641",
    "18362.239.19h1_release_svc_prod1.190628-1641",
    "",
    1531656000 
}

}; // end of WindowsFingerprint::_builds_information

void WindowsFingerprint::generate()
{
    std::vector<bool> oem{ true, false };
    _oem = this->choise(oem);

    _product_name = static_cast<ProductName>(rnd(0, static_cast<int>(ProductName::ProductNameCount)));
}



std::string WindowsFingerprint::system_name() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::service_pack() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::edition() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::product_name() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::installation_type() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

int WindowsFingerprint::installation_date() const
{
    throw std::logic_error{ "Not implemented" };
    return 0;

}

std::string WindowsFingerprint::build() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::build_guid() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::csd_version() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};

}

int WindowsFingerprint::csd_build_number() const
{
    throw std::logic_error{ "Not implemented" };
    return 0;
}

std::string WindowsFingerprint::build_lab() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::build_lab_ex() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::current_version() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

std::string WindowsFingerprint::current_build() const
{
    throw std::logic_error{ "Not implemented" };
    return std::string{};
}

int WindowsFingerprint::current_build_number() const
{
    throw std::logic_error{ "Not implemented" };
    return 0;
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
