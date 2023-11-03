/*
 * Copyright (C) Deutsche Telekom AG
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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
    if (r == 1) {
        uint32_t val = ntohl(addr.s_addr);
        return telemetrifyQ_commonQ_utilsQ_IPv4AddressG_new($NEWTUPLE(4,
            to$int(val >> 24 & 0xff), to$int(val >> 16 & 0xff), to$int(val >> 8 & 0xff), to$int(val & 0xff)));
    }
    return B_None;
}

telemetrifyQ_commonQ_utilsQ_IPv6Address telemetrifyQ_commonQ_utilsQ_IPv6AddressD_try_parse (B_str s) {
    struct in6_addr addr;

    int r = inet_pton(AF_INET6, fromB_str(s), &addr);
    if (r == 1) {
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
