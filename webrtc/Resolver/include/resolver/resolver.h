#ifndef RESOLVER_H
#define RESOLVER_H

#include <memory>

#include "Base/resolverbase.h"
#ifdef WIN32
    #include "win32/winresolver.h"
#elif
    /// some other platform include
#endif

class Resolver {
public:
    explicit Resolver();
    virtual ~Resolver();

    bool resolve_address(const std::string& address);

private:
    std::unique_ptr<ResolverBase> resolver_;
};

#endif // RESOLVER_H
