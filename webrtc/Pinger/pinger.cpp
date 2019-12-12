#include "pinger.h"

Pinger::Pinger()
#ifdef WIN32
    : pinger_(std::make_unique<WinPinger>())
#elif
#endif
{ }

bool Pinger::ping_address(const std::string &address) {
    return pinger_->ping_address(address);
}
