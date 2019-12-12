#ifndef WINRESOLVER_H
#define WINRESOLVER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#include "../Base/resolverbase.h"

class WinResolver : public ResolverBase
{
public:
    explicit WinResolver();
    virtual ~WinResolver();

    bool resolve_address(const std::string &address) override;
};

#endif // WINRESOLVER_H
