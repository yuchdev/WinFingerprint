#include "firewall.h"

Firewall::Firewall()
#ifdef WIN32
    : fw_ (std::make_unique<WFP>())
#elif
    /// some other platform init
#endif
{ }

Firewall::~Firewall()
{ }

bool Firewall::add_to_exceptions(const std::string &blob_path) {
    return fw_->add_to_exceptions(blob_path);
}

bool Firewall::deny_all_except() {
    return fw_->deny_all_except();
}

bool Firewall::allow_all() {
    return fw_->allow_all();
}
