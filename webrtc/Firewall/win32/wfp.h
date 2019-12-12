#ifndef WFP_H
#define WFP_H

#include <Winsock2.h>
#include <conio.h>
#include <strsafe.h>
#include <fwpmu.h>
#include <stdint.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <winnetwk.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <socketapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <locale>
#include <codecvt>

#include "Base/firewallbase.h"

class WFP : public FirewallBase {
public:
    explicit WFP();
    virtual ~WFP();

    bool add_to_exceptions(const std::string& blob_path = std::string()) override;

    bool deny_all_except() override;
    bool allow_all() override;

private:
    void close_all_blobs();
    void get_error(LPTSTR fname, DWORD ec);

private:
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>  converter_;
    std::vector<uint64_t>                                   filter_ids_;
    std::vector<FWP_BYTE_BLOB*>                             exclusion_blobs_;

    HANDLE          engine_handle_;
    GUID            sublayer_guid_;
};


#endif // WFP_H
