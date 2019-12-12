#ifndef WINPINGER_H
#define WINPINGER_H

#include <winsock2.h>
#include <iphlpapi.h>
#include <IcmpAPI.h>
#include <string>

#include "Base/pingerbase.h"

class WinPinger : public PingerBase {
public:
    WinPinger() = default;
    ~WinPinger() = default;

    bool ping_address(const std::string &address) override;
};

#endif // WINPINGER_H
