#include <arpa/inet.h>

#ifdef __APPLE__ && __MACH__
    #ifndef s6_addr16
        #define s6_addr16 __u6_addr.__u6_addr16
    #endif
#endif

void telemetrifyQ_commonQ_utilsQ___ext_init__() {
    // NOP
}

B_NoneType telemetrifyQ_commonQ_utilsQ_unsafe_list_append (B_list target, $WORD item) {
    B_Sequence W_768 = (B_Sequence)B_SequenceD_listG_witness;
    ((B_NoneType (*) (B_Sequence, B_list, $WORD))W_768->$class->append)(W_768, target, item);
    return B_None;
}

telemetrifyQ_commonQ_utilsQ_IPv4Address telemetrifyQ_commonQ_utilsQ_IPv4AddressD_try_parse (B_str s) {
    struct in_addr addr;

    int r = inet_pton(AF_INET, fromB_str(s), &addr);
    if (r == 0) {
        return telemetrifyQ_commonQ_utilsQ_IPv4AddressG_new($NEWTUPLE(4,
            to$int(addr.s_addr >> 24 & 0xff), to$int(addr.s_addr >> 16 & 0xff), to$int(addr.s_addr >> 8 & 0xff), to$int(addr.s_addr & 0xff)));
    }
    return B_None;
}

telemetrifyQ_commonQ_utilsQ_IPv6Address telemetrifyQ_commonQ_utilsQ_IPv6AddressD_try_parse (B_str s) {
    struct in6_addr addr;

    int r = inet_pton(AF_INET6, fromB_str(s), &addr);
    if (r == 0) {
        return telemetrifyQ_commonQ_utilsQ_IPv6AddressG_new($NEWTUPLE(8,
            to$int(ntohs(addr.s6_addr16[0])),
            to$int(ntohs(addr.s6_addr16[1])),
            to$int(ntohs(addr.s6_addr16[2])),
            to$int(ntohs(addr.s6_addr16[3])),
            to$int(ntohs(addr.s6_addr16[4])),
            to$int(ntohs(addr.s6_addr16[5])),
            to$int(ntohs(addr.s6_addr16[6])),
            to$int(ntohs(addr.s6_addr16[7]))));
    }
    return B_None;
}
