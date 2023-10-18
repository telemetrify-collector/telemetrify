include nidvars.mk

# The default testenv should be a "quick" testenv, containing a simple test that
# is quick to run.
DEFAULT_TESTENV?=quick

# Include standard NID (NSO in Docker) package Makefile that defines all
# standard make targets
include nidned.mk

ifeq ($(DEV),true)
	OUTPUT=out/dev
else
	OUTPUT=out/rel
endif

Dockerfile: prepare-telemetrify-packages

prepare-telemetrify-packages:
	$(MAKE) -C .. build-packages
	rsync -rupE ../packages/telemetrify packages

.PHONY: copy-telemetrify-packages
