#include <winfp/windows_fingerprint.h>

#include <ctime>
#include <cassert>
#include <algorithm>

using namespace antios;

// static

void WindowsFingerprint::generate_product_id()
{
    std::string alphabet{ "0123456789" };
    std::string ret{ 23 };
    ret = random_string(5, alphabet);
    ret += '-';
    ret += _oem ? "OEM" : random_string(3, alphabet);
    ret += '-';
    ret += random_string(7, alphabet);
    ret += '-';
    ret += random_string(5, alphabet);
    _product_id.swap(ret);
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

std::string WindowsFingerprint::get_product_name() const
{
    std::string ret = _build_info.product_version;
    ret += ' ';
    ret += WindowsFingerprintData::get_edition(_edition);
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
