#include <winfp/winfp_data.h>

using namespace antios;

std::vector<antios::WindowsBuildInfo> antios::WindowsFingerprint::_builds_information = {
    
    // Windows 7
    WindowsBuildInfo{
        "Windows 7", "", "6.1", "7600", "6.1.7600.16385", "7600.win7_rtm.090713-1255", "7600.16385.win7_rtm.090713-1255", "", 1256212800
    },
    // Windows 7 SP 1
    WindowsBuildInfo{
        "Windows 7", "Service Pack 1", "6.1", "7601", "6.1.7601.16385", "7601.win7_rtm.090713-1255", "7601.16385.win7_rtm.090713-1255", "1130", 1256212800
    },
    WindowsBuildInfo{
        "Windows 7", "Service Pack 1", "6.1", "7601", "6.1.7601.17514", "7601.win7sp1_rtm.101119-1850", "7601.16385.win7sp1_rtm.101119-1850", "1130", 1256212800
    },
    WindowsBuildInfo{
        "Windows 7", "Service Pack 1", "6.1", "7601", "6.1.7601.24214", "7601.win7sp1_ldr_escrow.180801-1700", "7601.24214.win7sp1_ldr_escrow.180801-1700", "1130", 1256212800
    },

    // Windows 10 1809
    WindowsBuildInfo{
        "Windows 10", "1809", "9.0", "17763", "10.0.17763.557", "17763.rs5_release_svc_prod1.190606-1817", "17763.557.rs5_release_svc_prod1.190606-1817", "", 1561896000
    },

};

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
