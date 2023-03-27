#include <arpa/inet.h>

void nsoapiQ_utilsQ___ext_init__() {
    // NOP
}

nsoapiQ_utilsQ_IPv4Address nsoapiQ_utilsQ_IPv4AddressD_try_parse (B_str s) {
    struct in_addr addr;

    int r = inet_pton(AF_INET, fromB_str(s), &addr);
    if (r == 0) {
        return nsoapiQ_utilsQ_IPv4AddressG_new($NEWTUPLE(4,
            toB_int(addr.s_addr >> 24 & 0xff), toB_int(addr.s_addr >> 16 & 0xff), toB_int(addr.s_addr >> 8 & 0xff), toB_int(addr.s_addr & 0xff)));
    }
    return B_None;
}

nsoapiQ_utilsQ_IPv6Address nsoapiQ_utilsQ_IPv6AddressD_try_parse (B_str s) {
    struct in6_addr addr;

    int r = inet_pton(AF_INET6, fromB_str(s), &addr);
    if (r == 0) {
        return nsoapiQ_utilsQ_IPv6AddressG_new($NEWTUPLE(8,
            toB_int(ntohs(addr.s6_addr16[0])),
            toB_int(ntohs(addr.s6_addr16[1])),
            toB_int(ntohs(addr.s6_addr16[2])),
            toB_int(ntohs(addr.s6_addr16[3])),
            toB_int(ntohs(addr.s6_addr16[4])),
            toB_int(ntohs(addr.s6_addr16[5])),
            toB_int(ntohs(addr.s6_addr16[6])),
            toB_int(ntohs(addr.s6_addr16[7]))));
    }
    return B_None;
}
