include nidvars.mk

# The default testenv should be a "quick" testenv, containing a simple test that
# is quick to run.
DEFAULT_TESTENV?=ios-xe-ipsla-mock

# Include standard NID (NSO in Docker) package Makefile that defines all
# standard make targets
include nidpackage.mk

Dockerfile: prepare-telemetrify

prepare-telemetrify:
	cp -rp ../telemetrify-nid-base/* .
	cp -rp telemetrify-nid-addon/* .
	cp -rp ../telemetrify-core telemetrify-ext/deps
	$(MAKE) -C telemetrify-ext/deps/telemetrify-core test
	$(MAKE) -f telemetrify-ext.mk prepare-telemetrify-pkg

.PHONY: prepare-telemetrify

clean-telemetrify:
	@echo "Run delete target only as a basic test if files are present"
	-[ -d telemetrify-ext ] && $(MAKE) -f telemetrify-ext.mk clean-telemetrify-pkg
	rm -rf packages/telemetrify
	rm -rf telemetrify-ext
	rm -f telemetrify-ext.mk

.PHONY: clean-telemetrify

generate-test-jobs:
	nid/generate-test-jobs > test-jobs.yaml
