SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
ifeq ($(DEV),true)
	BUILD_PATH=$(PROJECT_DIR)/out/dev
else
	BUILD_PATH=$(PROJECT_DIR)/out/rel
endif
ARGS?=maapi-schema
REPLAY?=replays/maapi-schema-bare.raw.gz

start:
	@(zcat $(REPLAY) | nc -l 4569 &)

stop:
	-@pkill -f "^nc -l 4569$$"

test:
	$(BUILD_PATH)/bin/nsoapi.test $(ARGS)

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/nsoapi.test --rts-wthreads 1 $(ARGS)

.PHONY: start stop test test-debug
