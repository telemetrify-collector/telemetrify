FROM streaming-nso/nso:6.1.4

RUN rm /var/opt/ncs/packages/juniper-junos-nc-4.11/load-dir/junos.fxs && \
    rm -rf /var/opt/ncs/packages/ned-* && \
    apt update && \
    apt install -y sshpass gdb
