#include "ethernettools.h"

#include <string>
#include <iostream>

int main(int argc, char *argv[]) {

    EthernetTools tools;
    std::cout << "Primary Adapter: \n" << tools.get_primary_adapter() << std::endl << std::endl;
    bool r = tools.set_ip_address(tools.get_primary_adapter(),
                                  std::string("192.168.1.3"),
                                  std::string("255.255.255.0"),
                                  std::string("192.168.0.1"));

    if (!r) {
        std::cout << "Set ip failed!" << std::endl;
    }
    else {
        std::cout << "Setting ip address success..." << std::endl;
    }

    std::string c;
    std::cin >> c;
    return 0;
}
