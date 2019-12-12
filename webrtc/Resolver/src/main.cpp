#include "resolver.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf_s("Please specify the address\n");
        exit(0);
    }

    Resolver r;
    if (!r.resolve_address(std::string(argv[1]))) { printf_s("Filed resolve address: '%s'\n", argv[1]); }
    else { printf_s("Success resolve address: '%s'\n", argv[1]); }

    return 0;
}
