#include <winfp/winfp_data.h>

using namespace antios;

// static
std::vector<int> antios::WindowsFingerprint::_system_versions = { 7,8,10 };

std::map<int, std::string> WindowsFingerprint::_system_version_name = {
    {7, "Windows 7"},
    {8, "Windows 8"},
    {10, "Windows 10"}
};

void WindowsFingerprint::generate()
{
    _windows_version = this->choise(_system_versions);
}


int WindowsFingerprint::system_version() const
{
    return _windows_version;
}

std::string WindowsFingerprint::system_name() const
{
    auto ver = _system_version_name.find(_windows_version);
    assert(ver != _system_version_name.end());
    return (*ver).second;
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
