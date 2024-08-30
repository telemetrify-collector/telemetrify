SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
BUILD_PATH=$(PROJECT_DIR)/telemetrify-core/out
ARGS?=maapi-schema
NCS_D?=ncs

start:
	ncs --cd $(SELF_DIR)$(NCS_D)
	ncs --wait-started 600

stop:
	ncs --stop

test:
	$(BUILD_PATH)/bin/telemetrify.test $(ARGS)

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/telemetrify.test --rts-wthreads 1 $(ARGS)

cli:
	ncs_cli -u admin

.PHONY: start stop test test-debug cli
