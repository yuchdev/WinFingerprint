#include "ethernettools.h"

EthernetTools::EthernetTools()
#ifdef WIN32
    : eth_tools_(std::make_unique<WinEthernet>())
#elif
#endif
{ }

EthernetTools::~EthernetTools()
{ }

const std::vector<Adapter> &EthernetTools::get_adapters() {
    return eth_tools_->get_adapters();
}

Adapter EthernetTools::get_primary_adapter() const {
    return eth_tools_->get_primary_adapter();
}

bool EthernetTools::set_ip_address(const Adapter &adapter, const std::string &ip, const std::string& mask, const std::string& gateway) {
    return eth_tools_->set_ip_address(adapter, ip, mask, gateway);
}
