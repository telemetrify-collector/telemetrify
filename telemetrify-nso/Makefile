include nidvars.mk

# The default testenv should be a "quick" testenv, containing a simple test that
# is quick to run.
DEFAULT_TESTENV?=ios-xe-ipsla-mock

# Include standard NID (NSO in Docker) package Makefile that defines all
# standard make targets
include nidpackage.mk

ACTON_CMD_PATH := $(shell which acton)
ifeq ($(ACTON_CMD_PATH),)
  $(error Acton compiler not found. Please run ./actup to install Acton locally in this project or see https://www.acton-lang.org/install/ for more options)
endif
ACTON_DIST_PATH := $(abspath $(dir $(ACTON_CMD_PATH))..)

Dockerfile: prepare-telemetrify

prepare-telemetrify:
	mkdir -p acton
	if [ -n "$$(which rsync)" ]; then rsync -avE $(ACTON_DIST_PATH)/. acton; else cp -rp $(ACTON_DIST_PATH)/. acton; fi
	cp -rp ../telemetrify-nid-base/. .
	cp -rp telemetrify-nid-addon/. .
	mkdir -p packages/telemetrify/src/acton/telemetrify-ext/deps/telemetrify_core
	cp -rp ../telemetrify-core/. packages/telemetrify/src/acton/telemetrify-ext/deps/telemetrify_core # Workaround https://github.com/actonlang/acton/issues/1886

.PHONY: prepare-telemetrify

clean-telemetrify:
	rm -rf acton
	rm -rf packages/telemetrify

.PHONY: clean-telemetrify

generate-test-jobs:
	nid/generate-test-jobs > test-jobs.yaml
