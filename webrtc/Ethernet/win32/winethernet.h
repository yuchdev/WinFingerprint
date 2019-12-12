#ifndef WINETHERNET_H
#define WINETHERNET_H

#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <locale>
#include <codecvt>

#include "Base/ethernettoolsbase.h"
#include "utils/utils.h"

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

class WinEthernet : public EthernetToolsBase {
public:
    explicit WinEthernet();
    virtual ~WinEthernet();

    Adapter get_primary_adapter() const override;

    bool set_ip_address(const Adapter& adapter, const std::string& ip, const std::string& mask, const std::string& gateway) override;

private:
    void query_all_adapters() override;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>  converter_;
    std::string  get_friendly_name_by_index(const std::size_t index);

    Adapter current_changed_adapter_;
};

#endif // WINETHERNET_H
