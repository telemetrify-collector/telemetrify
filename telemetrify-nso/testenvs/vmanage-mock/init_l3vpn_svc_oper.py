#!/usr/bin/env python3
import _ncs
import ncs
import ncs.maapi
import ncs.maagic

#with ncs.maapi.single_write_trans('admin', 'system', db=_ncs.RUNNING) as t:
with ncs.maapi.single_write_trans('admin', 'system', db=_ncs.OPERATIONAL) as t:
    service = ncs.maagic.get_node(t, "/l3vpn-svc/sites/site{2000000002.000228}/site-network-accesses/site-network-access{001.2000000002}")
    # site = service._parent._parent._parent
    # site_id = site.site_id
    # sap_vpn_id, sap_no = site_id.split('.')
    # service.vars.site_id = sap_no.lstrip('0')
    service.vars.hostname = "de-bsp-aachen-ce-3" #SITE_VARIABLES[site_id]['hostname']
    service.vars.wan_interface.name = 'GigabitEthernet2'
    service.vars.wan_interface.ipv4_address = "10.1.1.1" #SITE_VARIABLES[site_id]['wan_prefix']
    service.vars.wan_interface.ipv4_prefix_length = "24"

    service = ncs.maagic.get_node(t, "/l3vpn-svc/sites/site{2000000002.000230}/site-network-accesses/site-network-access{001.2000000002}")
    # site = service._parent._parent._parent
    # site_id = site.site_id
    # sap_vpn_id, sap_no = site_id.split('.')
    # service.vars.site_id = sap_no.lstrip('0')
    service.vars.hostname = "de-bsp-chemni-ce-2" #SITE_VARIABLES[site_id]['hostname']
    service.vars.wan_interface.name = 'GigabitEthernet2'
    service.vars.wan_interface.ipv4_address = "10.1.3.1" #SITE_VARIABLES[site_id]['wan_prefix']
    service.vars.wan_interface.ipv4_prefix_length = "24"

    t.apply()
