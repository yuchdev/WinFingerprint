#include "firewall.h"
#include <string>


int main(int argc, char *argv[]) {

    Firewall f;
    f.add_to_exceptions(argv[1]);

    if (!f.deny_all_except()) {
        printf_s("Error code: '%lu'\n", GetLastError());
    }

    f.allow_all();
    return 0;
}
