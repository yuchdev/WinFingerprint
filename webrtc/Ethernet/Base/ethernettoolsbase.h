#ifndef ETHERNETTOOLSBASE_H
#define ETHERNETTOOLSBASE_H

#include "utils/types.h"
#include <vector>

class EthernetToolsBase {
public:
    explicit EthernetToolsBase();
    virtual ~EthernetToolsBase();

    virtual const std::vector<Adapter>& get_adapters();

    virtual Adapter get_primary_adapter() const = 0;

    virtual bool set_ip_address(const Adapter& adapter, const std::string& ip, const std::string& mask, const std::string& gateway) = 0;

protected:
    virtual void query_all_adapters() = 0;

protected:
    std::vector<Adapter> adapters_;
};

#endif // ETHERNETTOOLSBASE_H
