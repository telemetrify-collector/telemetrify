FROM gitlab.dev.terastrm.net:4567/abs/dt-mplsnet/nso:6.1.4

RUN rm /var/opt/ncs/packages/juniper-junos-nc-4.11/load-dir/junos.fxs && \
    apt update && \
    apt install -y sshpass gdb
