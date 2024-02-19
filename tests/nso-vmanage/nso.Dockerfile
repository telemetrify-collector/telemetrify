FROM telemetrify-nso/nso:${NSO_VERSION}

RUN rm -rf /var/opt/ncs/packages/ned-ios-* && \
    apt update && \
    apt install -y sshpass gdb
