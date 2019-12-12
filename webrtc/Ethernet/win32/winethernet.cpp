#include "winethernet.h"

WinEthernet::WinEthernet() {
    query_all_adapters();
}

WinEthernet::~WinEthernet()
{

}

Adapter WinEthernet::get_primary_adapter() const {
    Adapter pr_adapter;
    for (const auto &adapter : adapters_) {
        if (adapter.ip_gateway_ != std::string("0.0.0.0")) {
            pr_adapter = adapter;
        }
    }

    return pr_adapter;
}

bool WinEthernet::set_ip_address(const Adapter &adapter, const std::string &ip, const std::string& mask, const std::string &gateway) {
    bool result = false;
    if (adapter.name_.empty()) {
        printf_s("Adapter is not valid!\n");
        return result;
    }
    /// save current adaper params
    current_changed_adapter_ = adapter;

    STARTUPINFOA info;
    PROCESS_INFORMATION proc_info;
    ZeroMemory(&info, sizeof(STARTUPINFOA));
    ZeroMemory(&proc_info, sizeof(PROCESS_INFORMATION));

//    DWORD u_ip = inet_addr(ip.data());
//    in_addr addr;
//    addr.S_un.S_addr = htonl(~((1 << (32 - u_ip)) - 1));

//    printf_s("ADDR: '%s'  MASK: '%s'\n", ip.data(), inet_ntoa(addr));

    std::stringstream cmd;
    cmd << " interface ipv4 set address name=\"" << adapter.friendly_name_ << "\" static " << ip << " " << mask << " " << gateway;
    result = CreateProcessA("C:\\Windows\\System32\\netsh.exe", (LPSTR)cmd.str().data(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &info, &proc_info);
    if (!result) {
        printf_s("Error exec netsh '%s'\n", strerror(GetLastError()));
    }
    WaitForSingleObject(proc_info.hProcess, INFINITE);
    CloseHandle(proc_info.hProcess);
    CloseHandle(proc_info.hThread);

    return result;
}

void WinEthernet::query_all_adapters() {
    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
    UINT i;

    tm newtime;
    char buffer[32];
    errno_t error;

    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
    pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
    if (!pAdapterInfo) {
        printf_s("Error allocating memory needed to call GetAdaptersinfo\n");
        return;
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
        if (!pAdapterInfo) {
            printf_s("Error allocating memory needed to call GetAdaptersinfo\n");
            return;
        }
    }


    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
        pAdapter = pAdapterInfo;
        while (pAdapter) {
            Adapter adapter;

            adapter.combo_index_ = pAdapter->ComboIndex;
            adapter.name_ = pAdapter->AdapterName;
            adapter.description_ = pAdapter->Description;

            for (i = 0; i < pAdapter->AddressLength; i++) {
                if (i == (pAdapter->AddressLength - 1)) {
                    adapter.hw_addr_ += ToHex<unsigned char>(pAdapter->Address[i], false);
                    adapter.hw_addr_ += '.';
                }
                else {
                    adapter.hw_addr_ += ToHex<unsigned char>(pAdapter->Address[i], false);
                    adapter.hw_addr_ += '-';
                }
            }

            adapter.index_ = pAdapter->Index;

            adapter.friendly_name_ = get_friendly_name_by_index(adapter.index_);
            if (adapter.friendly_name_.empty()) {
                if (pAdapterInfo) FREE(pAdapterInfo);
                printf_s("Can't get friendly name of adapter index: '%lu'\n", adapter.index_);
            }

            switch (pAdapter->Type) {
            case MIB_IF_TYPE_OTHER:
                adapter.type_ = "Other";
                break;
            case MIB_IF_TYPE_ETHERNET:
                adapter.type_ = "Ethernet";
                break;
            case MIB_IF_TYPE_TOKENRING:
                adapter.type_ = "Token Ring";
                break;
            case MIB_IF_TYPE_FDDI:
                adapter.type_ = "FDDI";
                break;
            case MIB_IF_TYPE_PPP:
                adapter.type_ = "PPP";
                break;
            case MIB_IF_TYPE_LOOPBACK:
                adapter.type_ = "Lookback";
                break;
            case MIB_IF_TYPE_SLIP:
                adapter.type_ = "Slip";
                break;
            default:
                adapter.type_ = "Unknown type: " + std::to_string(pAdapter->Type);
                break;
            }

            adapter.ip_addr_        = pAdapter->IpAddressList.IpAddress.String;
            adapter.ip_mask_        = pAdapter->IpAddressList.IpMask.String;
            adapter.ip_gateway_     = pAdapter->GatewayList.IpAddress.String;

            if (pAdapter->DhcpEnabled) {
                adapter.is_dhcp_ = true;
                adapter.ip_dhcp_addr_ = pAdapter->DhcpServer.IpAddress.String;
                error = _localtime32_s(&newtime, (__time32_t*) &pAdapter->LeaseObtained);
                if (error) {
                    printf("Invalid Argument to _localtime32_s\n");
                }
                else {
                    error = asctime_s(buffer, 32, &newtime);
                    if (error) {
                        printf("Invalid Argument to asctime_s\n");
                    }
                    else {
                        adapter.dhcp_lease_obtained_ = buffer;
                    }
                }

                error = _localtime32_s(&newtime, (__time32_t*) &pAdapter->LeaseExpires);
                if (error) {
                    printf("Invalid Argument to _localtime32_s\n");
                }
                else {
                    error = asctime_s(buffer, 32, &newtime);
                    if (error) {
                        printf("Invalid Argument to asctime_s\n");
                    }
                    else {
                        adapter.dhcp_lease_expired_ = buffer;
                    }
                }
            }
            else{
                adapter.is_dhcp_ = false;
            }

            if (pAdapter->HaveWins) {
                adapter.is_wins_ = true;
                adapter.ip_wins_primary_ = pAdapter->PrimaryWinsServer.IpAddress.String;
                adapter.ip_wins_secondary_ = pAdapter->SecondaryWinsServer.IpAddress.String;
            }
            else{
                adapter.is_wins_ = false;
            }

            pAdapter = pAdapter->Next;
            printf("\n");
            adapters_.push_back(adapter);
        }
    }
    else {
        printf("GetAdaptersInfo failed with error: %d\n", dwRetVal);
    }

    if (pAdapterInfo) FREE(pAdapterInfo);
}

std::string WinEthernet::get_friendly_name_by_index(const std::size_t index) {
    std::string result_name;
    PIP_ADAPTER_ADDRESSES pAddresses = NULL;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
    ULONG flags  = GAA_FLAG_INCLUDE_PREFIX;
    ULONG outBufLen = 256;
    ULONG family = AF_INET;
    outBufLen = sizeof (IP_ADAPTER_ADDRESSES);
    DWORD ret = 0;
    const DWORD max_tries = 3;
    DWORD tries = 0;
    do {
        pAddresses = (IP_ADAPTER_ADDRESSES *) MALLOC(outBufLen);
        if (pAddresses == NULL) {
            printf_s("Memory allocation failed for IP_ADAPTER_ADDRESSES struct!\n");
            return result_name;
        }

         ret = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);
         if (ret == ERROR_BUFFER_OVERFLOW) {
             FREE(pAddresses);
             pAddresses = NULL;
         }
         else { break; }
         tries++;
    }
    while((ret == ERROR_BUFFER_OVERFLOW) && (tries < max_tries));

    if (pAddresses == NULL) {
        printf_s("Memory allocation failed for IP_ADAPTER_ADDRESSES struct!\n");
        return result_name;
    }

    DWORD dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);
    if (dwRetVal == NO_ERROR) {
        pCurrAddresses = pAddresses;
        while (pCurrAddresses) {
            if (pCurrAddresses->IfIndex == index) {
                result_name = converter_.to_bytes(pCurrAddresses->FriendlyName);
                break;
            }

            pCurrAddresses = pCurrAddresses->Next;
        }
    }

    FREE(pAddresses);
    return result_name;
}
