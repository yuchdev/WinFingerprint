#include <cstdio>

#include "pinger.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf_s("Please specify the ip address!\n");
        exit(0);
    }

    if (Pinger().ping_address(std::string(argv[1]))) {
        printf_s("Success ping address: '%s'\n", argv[1]);
    }
    else { printf_s("Failed ping address: '%s'\n", argv[1]); }
    return 0;
}
