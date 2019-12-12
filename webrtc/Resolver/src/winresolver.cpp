#include "winresolver.h"

WinResolver::WinResolver() { }
WinResolver::~WinResolver() { }

bool WinResolver::resolve_address(const std::string &address) {
    bool result = false;
    WSADATA wsa_data;
    in_addr addr;

    int ws_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (ws_result != 0) {
        printf_s("WSAStartup failed with code: '%d'\n", ws_result);
        return result;
    }

    hostent *remote_host = gethostbyname(address.data());
    if (remote_host == NULL) {
        DWORD ws_error = WSAGetLastError();
        switch (ws_error) {
        case WSAHOST_NOT_FOUND:
            printf_s("Host: '%s' not found!\n", address.data());
            return result;
        case WSANO_DATA:
            printf_s("No data Record found to host: '%s'", address.data());
            return result;
        default:
            printf_s("Error in get host by name function: '%ld\n'", ws_error);
            return result;
        }
    }
    else {
        addr.s_addr = *(u_long *) remote_host->h_addr_list[0];
        printf("IP Address: '%s'\n", inet_ntoa(addr));
        result = true;
    }
    return result;
}
