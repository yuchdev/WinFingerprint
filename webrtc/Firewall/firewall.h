#ifndef FIREWALL_H
#define FIREWALL_H

#include <memory>

#include "Base/firewallbase.h"
#ifdef WIN32
    #include "win32/wfp.h"
#elif
    /// some other platform include
#endif

class Firewall {
public:
    explicit Firewall();
    virtual ~Firewall();

    bool add_to_exceptions(const std::string& blob_path = std::string());
    bool deny_all_except();
    bool allow_all();

private:
    std::unique_ptr<FirewallBase> fw_;
};

#endif // FIREWALL_H
