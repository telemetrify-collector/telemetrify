/*
 * BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE
 * This file has been auto-generated by the confdc compiler.
 * Source: ../load-dir/junos-common-types.fxs
 * BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE BEWARE
 */

package com.example.nedjunos23_1yang.namespaces;

import com.tailf.conf.ConfNamespace;

/** Autogenerated namespace class for YANG module junos-common-types.yang */
public class junosCommonTypes extends ConfNamespace {
    public static final int hash = 103271231;
    public int hash() {
        return junosCommonTypes.hash;
    }

    public static final String id = "_ned-junos-23.1-yang-nc-1.0:ned-junos-23.1-yang-nc-1.0#http://yang.juniper.net/junos/common/types";
    public String id() {
        return junosCommonTypes.id;
    }

    public static final String uri = "_ned-junos-23.1-yang-nc-1.0:ned-junos-23.1-yang-nc-1.0#http://yang.juniper.net/junos/common/types";
    public String uri() {
        return junosCommonTypes.uri;
    }

    public String xmlUri() {
        return ConfNamespace.truncateToXMLUri(junosCommonTypes.uri);
    }

    public static final String prefix = "jt";
    public String prefix() {
        return junosCommonTypes.prefix;
    }

    public junosCommonTypes() {}

    public static int stringToHash(String str) {
        return ConfNamespace.stringToHash(str);
    }

    public static String hashToString(int hash) {
        return ConfNamespace.hashToString(hash);
    }

}