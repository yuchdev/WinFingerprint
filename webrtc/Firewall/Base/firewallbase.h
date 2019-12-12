#ifndef FIREWALLBASE_H
#define FIREWALLBASE_H

#include <vector>
#include <string>

class FirewallBase {
public:
    virtual bool add_to_exceptions(const std::string& blob_path = std::string()) = 0;
    virtual bool deny_all_except() = 0;
    virtual bool allow_all() = 0;

protected:
    std::vector<std::wstring> exclusion_paths_;
};

#endif // FIREWALLBASE_H
