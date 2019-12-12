#ifndef PINGER_H
#define PINGER_H

#include <memory>

#include "Base/pingerbase.h"

#ifdef WIN32
    #include "win32/winpinger.h"
#elif
#endif

class Pinger {
public:
    explicit Pinger();
    ~Pinger() = default;

    bool ping_address(const std::string& address);

private:
    std::unique_ptr<PingerBase> pinger_;
};

#endif // PINGER_H
