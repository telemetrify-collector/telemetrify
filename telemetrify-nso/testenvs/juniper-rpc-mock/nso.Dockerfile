ARG IMAGE_BASENAME
ARG DOCKER_TAG

FROM ${IMAGE_BASENAME}/nso:${DOCKER_TAG}

RUN rm -rf /var/opt/ncs/packages/ned-ios-* && \
    apt update && \
    apt install -y sshpass gdb netcat-openbsd
