include ../testenv-common.mk

# and the $(MAKEFILE_LIST) [ Makefile ../quick/quick-common.mk ../testenv-common.mk ../../nidcommon.mk ]
# To get the name of the testenv, take the first Makefile ("Makefile") and
# determine the base directory name ("quick-alu-sr"). The "quick" directory is
# not a testenv because it does not contain a Makefile.
TESTENV:=$(shell basename $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST)))))

SHELL=/bin/bash
SELF_DIR:=$(dir $(firstword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
BUILD_PATH=$(PROJECT_DIR)/telemetrify-core/out
ARGS?=netconf-client-vr-vmx
CNT_PREFIX?=test-$(TESTENV)-$(shell whoami)
VR_NAME?=vmx1
VR_CNT=$(CNT_PREFIX)-$(VR_NAME)

start:
	docker run -it -d $(DOCKER_ARGS) --net=host --name $(CNT_PREFIX)-nso ned-juniper-junos-nc/testnso:${NSO_VERSION}-$(shell whoami)
	docker run -it -d $(DOCKER_ARGS) --privileged --name $(CNT_PREFIX)-$(VR_NAME) -p 10022:22 -p 10830:830 gitlab.dev.terastrm.net:4567/abs/vrnetlab/vr-vmx:23.1R1.8 --trace
	@echo "Awaiting healthy ${VR_CNT} ..."
	@while [ "$$(docker inspect -f {{.State.Health.Status}} $(VR_CNT))" != "healthy" ]; do sleep 1; done
	$(MAKE) config-nso


config-nso:
	$(MAKE) loadconf FILE=add-vmx.xml
	$(MAKE) runcmdJ CMD="request devices fetch-ssh-host-keys"
	$(MAKE) runcmdJ CMD="request devices sync-from"

stop:
	docker ps -aq --filter label=testenv.name=$(CNT_PREFIX) | $(XARGS) docker rm -vf

test:
	$(BUILD_PATH)/bin/acton_streamer.test $(ARGS)

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/acton_streamer.test --rts-wthreads 1 $(ARGS)

cli:
	ncs_cli -u admin

.PHONY: start stop test test-debug cli
