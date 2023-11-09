FROM telemetrify-nso/nso:6.1.4

RUN rm -rf /var/opt/ncs/packages/ned-junos-* && \
    apt update && \
    apt install -y sshpass gdb
