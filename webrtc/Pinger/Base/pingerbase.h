#ifndef PINGERBASE_H
#define PINGERBASE_H

#include <string>

class PingerBase {
public:
    virtual bool ping_address(const std::string& address) = 0;
};

#endif // PINGERBASE_H
