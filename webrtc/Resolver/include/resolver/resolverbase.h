#ifndef RESOLVERBASE_H
#define RESOLVERBASE_H

#include <string>

class ResolverBase {
public:
    virtual bool resolve_address(const std::string& address) = 0;
};

#endif // RESOLVERBASE_H
