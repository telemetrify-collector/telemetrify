SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
DOCKER_USER:=$(shell id -u):$(shell id -g)
ifeq ($(DEV),true)
	BUILD_PATH=$(PROJECT_DIR)/out/dev
else
	BUILD_PATH=$(PROJECT_DIR)/out/rel
endif
NCS_D?=ncs

start:
	DOCKER_USER=$(DOCKER_USER) docker compose up

stop:
	docker compose down

test:
	$(BUILD_PATH)/bin/tsdb.test

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/prometheusapi.test --rts-wthreads 1 $(ARGS)

.PHONY: start stop test test-debug cli
