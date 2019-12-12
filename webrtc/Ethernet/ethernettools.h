#ifndef ETHERNETTOOLS_H
#define ETHERNETTOOLS_H

#include <memory>

#include "Base/ethernettoolsbase.h"

#ifdef WIN32
#include "win32/winethernet.h"
#elif
#endif

class EthernetTools {
public:
    explicit EthernetTools();
    virtual ~EthernetTools();

    const std::vector<Adapter>& get_adapters();
    Adapter get_primary_adapter() const;
    bool set_ip_address(const Adapter& adapter, const std::string& ip, const std::string &mask, const std::string &gateway);

private:
    std::unique_ptr<EthernetToolsBase> eth_tools_;
};

#endif // ETHERNETTOOLS_H
