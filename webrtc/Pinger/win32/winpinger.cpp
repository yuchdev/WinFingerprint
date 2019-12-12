#include "winpinger.h"

bool WinPinger::ping_address(const std::string &address) {
    unsigned long ipaddr    = INADDR_NONE;
    char SendData[32]       = "Data Buffer";
    bool result             = false;
    LPVOID ReplyBuffer      = NULL;
    DWORD dwRetVal          = 0;
    DWORD ReplySize         = 0;
    HANDLE hIcmpFile;

    if (address.empty()) {
        printf_s("Specify address to ping!\n");
        return result;
    }

    ipaddr = inet_addr(address.data());
    if (ipaddr == INADDR_NONE) {
        printf_s("Invalid address: '%s'\n", address.data());
        return result;
    }

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE) {
        DWORD err = GetLastError();
        printf_s("IcmpCreatefile returned error: '%lu' Text: '%s'\n", err, strerror(err));
        return result;
    }

    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    ReplyBuffer = (VOID*) malloc(ReplySize);
    if (ReplyBuffer == NULL) {
        printf_s("Unable to allocate memory\n");
        return result;
    }

    dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData), NULL, ReplyBuffer, ReplySize, 1000);
    if (dwRetVal != 0) {
        PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;
        struct in_addr ReplyAddr;
        ReplyAddr.S_un.S_addr = pEchoReply->Address;
        printf_s("Recived from: '%s' time: '%lu' ms.\n", inet_ntoa( ReplyAddr ), pEchoReply->RoundTripTime);
        result = true;
    }
    else {
        printf_s("IcmpSendEcho returned error: '%lu'\n", GetLastError());
    }
    return result;
}
