#ifndef TYPES_H
#define TYPES_H

#include <string>

struct Adapter {
    std::size_t combo_index_;
    std::size_t index_;
    std::string name_;
    std::string friendly_name_;
    std::string description_;
    std::string hw_addr_;
    std::string type_;
    std::string ip_addr_;
    std::string ip_mask_;
    std::string ip_gateway_;
    std::string ip_dhcp_addr_;
    std::string ip_wins_primary_;
    std::string ip_wins_secondary_;
    std::string dhcp_lease_obtained_;
    std::string dhcp_lease_expired_;
    bool is_dhcp_;
    bool is_wins_;

    Adapter()
        : combo_index_  (0)
        , index_        (0)
        , is_dhcp_      (false)
        , is_wins_      (false)
    { }

    Adapter(const Adapter& a)
        : combo_index_          (a.combo_index_)
        , index_                (a.index_)
        , name_                 (a.name_)
        , friendly_name_        (a.friendly_name_)
        , description_          (a.description_)
        , hw_addr_              (a.hw_addr_)
        , type_                 (a.type_)
        , ip_addr_              (a.ip_addr_)
        , ip_mask_              (a.ip_mask_)
        , ip_gateway_           (a.ip_gateway_)
        , ip_dhcp_addr_         (a.ip_dhcp_addr_)
        , ip_wins_primary_      (a.ip_wins_primary_)
        , ip_wins_secondary_    (a.ip_wins_secondary_)
        , dhcp_lease_obtained_  (a.dhcp_lease_obtained_)
        , dhcp_lease_expired_   (a.dhcp_lease_expired_)
        , is_dhcp_              (a.is_dhcp_)
        , is_wins_              (a.is_wins_)
    { }

    Adapter(Adapter&& a)
        : combo_index_          (a.combo_index_)
        , index_                (a.index_)
        , name_                 (std::move(a.name_))
        , friendly_name_        (std::move(a.friendly_name_))
        , description_          (std::move(a.description_))
        , hw_addr_              (std::move(a.hw_addr_))
        , type_                 (std::move(a.type_))
        , ip_addr_              (std::move(a.ip_addr_))
        , ip_mask_              (std::move(a.ip_mask_))
        , ip_gateway_           (std::move(a.ip_gateway_))
        , ip_dhcp_addr_         (std::move(a.ip_dhcp_addr_))
        , ip_wins_primary_      (std::move(a.ip_wins_primary_))
        , ip_wins_secondary_    (std::move(a.ip_wins_secondary_))
        , dhcp_lease_obtained_  (std::move(a.dhcp_lease_obtained_))
        , dhcp_lease_expired_   (std::move(a.dhcp_lease_expired_))
        , is_dhcp_              (a.is_dhcp_)
        , is_wins_              (a.is_wins_)
    { }

    Adapter& operator=(const Adapter& a) {
        combo_index_          = a.combo_index_;
        index_                = a.index_;
        name_                 = a.name_;
        friendly_name_        = a.friendly_name_;
        description_          = a.description_;
        hw_addr_              = a.hw_addr_;
        type_                 = a.type_;
        ip_addr_              = a.ip_addr_;
        ip_mask_              = a.ip_mask_;
        ip_gateway_           = a.ip_gateway_;
        ip_dhcp_addr_         = a.ip_dhcp_addr_;
        ip_wins_primary_      = a.ip_wins_primary_;
        ip_wins_secondary_    = a.ip_wins_secondary_;
        dhcp_lease_obtained_  = a.dhcp_lease_obtained_;
        dhcp_lease_expired_   = a.dhcp_lease_expired_;
        is_dhcp_              = a.is_dhcp_;
        is_wins_              = a.is_wins_;

        return *this;
    }

    bool operator ==(const Adapter& a) {
        return (combo_index_            == a.combo_index_           &&
                index_                  == a.index_                 &&
                name_                   == a.name_                  &&
                friendly_name_          == a.friendly_name_         &&
                description_            == a.description_           &&
                hw_addr_                == a.hw_addr_               &&
                type_                   == a.hw_addr_               &&
                ip_addr_                == a.ip_addr_               &&
                ip_mask_                == a.ip_mask_               &&
                ip_gateway_             == a.ip_gateway_            &&
                ip_dhcp_addr_           == a.ip_dhcp_addr_          &&
                ip_wins_primary_        == a.ip_wins_primary_       &&
                ip_wins_secondary_      == a.ip_wins_secondary_     &&
                dhcp_lease_obtained_    == a.dhcp_lease_obtained_   &&
                dhcp_lease_expired_     == a.dhcp_lease_expired_    &&
                is_dhcp_                == a.is_dhcp_               &&
                is_wins_                == a.is_wins_);
    }

    friend std::ostream& operator << (std::ostream& os, const Adapter& a) {

        os << "============================================================================"
           << "\nCombo Index        : '" << a.combo_index_             << "' \n"
           << "Index                : '"   << a.index_                 << "' \n"
           << "Name                 : '"   << a.name_                  << "' \n"
           << "Friendly Name        : '"   << a.friendly_name_         << "' \n"
           << "Description          : '"   << a.description_           << "' \n"
           << "HW Address           : '"   << a.hw_addr_               << "' \n"
           << "Type                 : '"   << a.type_                  << "' \n"
           << "IP Address           : '"   << a.ip_addr_               << "' \n"
           << "IP Mask              : '"   << a.ip_mask_               << "' \n"
           << "IP Gateway           : '"   << a.ip_gateway_            << "' \n"
           << "IP DHCP              : '"   << a.ip_dhcp_addr_          << "' \n"
           << "IP WINS Primary      : '"   << a.ip_wins_primary_       << "' \n"
           << "IP WINS Secondary    : '"   << a.ip_wins_secondary_     << "' \n"
           << "IS DHCP              : '"   << a.is_dhcp_               << "' \n"
           << "IS WINS              : '"   << a.is_wins_               << "' \n"
           << "============================================================================";

        return os;
     }
};

#endif // TYPES_H
