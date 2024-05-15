include nidvars.mk

# The default testenv should be a "quick" testenv, containing a simple test that
# is quick to run.
DEFAULT_TESTENV?=ios-xe-ipsla-mock

# Include standard NID (NSO in Docker) package Makefile that defines all
# standard make targets
include nidpackage.mk

Dockerfile: prepare-telemetrify-bin

prepare-telemetrify-bin:
	$(MAKE) -C .. build test
	mkdir -p packages/telemetrify/bin
	cp -p ../out/bin/telemetrify.main.server packages/telemetrify/bin/

.PHONY: prepare-telemetrify-bin

generate-test-jobs:
	nid/generate-test-jobs > test-jobs.yaml
