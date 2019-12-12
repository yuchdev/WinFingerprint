#include "ethernettoolsbase.h"

EthernetToolsBase::EthernetToolsBase() { }

EthernetToolsBase::~EthernetToolsBase() { }

const std::vector<Adapter> &EthernetToolsBase::get_adapters() {
    return adapters_;
}
