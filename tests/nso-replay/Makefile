SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
BUILD_PATH=$(PROJECT_DIR)/out
ARGS?=maapi-schema
REPLAY?=replays/maapi-schema-ios-xr-pruned-50.raw.gz

start:
	@(zcat $(REPLAY) | nc -l 4569 &)

stop:
	-@pkill -f "^nc -l 4569$$"

test:
	$(BUILD_PATH)/bin/telemetrify.test $(ARGS)

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/telemetrify.test --rts-wthreads 1 $(ARGS)

.PHONY: start stop test test-debug
