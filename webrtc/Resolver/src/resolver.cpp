#include "resolver.h"

Resolver::Resolver()
#ifdef WIN32
    : resolver_(std::make_unique<WinResolver>())
#elif
    /// some other platform
#endif
{ }

Resolver::~Resolver()
{ }

bool Resolver::resolve_address(const std::string &address) {
    return resolver_->resolve_address(address);
}
