SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
ifeq ($(DEV),true)
	BUILD_PATH=$(PROJECT_DIR)/out/dev
else
	BUILD_PATH=$(PROJECT_DIR)/out/rel
endif
ARGS?=netconf-client-vr-vmx
VR_NAME?=test-vmx1

start:
	docker run -it -d --privileged --name $(VR_NAME) -p 10022:22 -p 10830:830 gitlab.dev.terastrm.net:4567/abs/vrnetlab/vr-vmx:23.1R1.8 --trace
	@echo "Awaiting healthy ${VR_NAME} ..."
	@while [ "$$(docker inspect -f {{.State.Health.Status}} $(VR_NAME))" != "healthy" ]; do sleep 1; done

stop:
	docker stop $(VR_NAME) && docker rm $(VR_NAME)

test:
	$(BUILD_PATH)/bin/nsoapi.test $(ARGS)

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/nsoapi.test --rts-wthreads 1 $(ARGS)

cli:
	ncs_cli -u admin

.PHONY: start stop test test-debug cli
