ARG NSO_VERSION

FROM telemetrify-nso/nso:${NSO_VERSION}

RUN rm -rf /var/opt/ncs/packages/ned-junos-* && \
    apt update && \
    apt install -y sshpass gdb
