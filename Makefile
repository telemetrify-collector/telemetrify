all: build
.PHONY: all

build:
	$(MAKE) -C telemetrify-core build
.PHONY: build

nso:
	$(MAKE) -C telemetrify-nso build
.PHONY: nso

generate-test-jobs:
	$(MAKE) -C telemetrify-nso generate-test-jobs

clean:
	$(MAKE) -C telemetrify-core clean
	$(MAKE) -C telemetrify-nso clean-telemetrify
.PHONY: clean

run-nogc:
	$(MAKE) -C telemetrify-core run-nogc
.PHONY: run-nogc

run:
	$(MAKE) -C telemetrify-core run
.PHONY: run

debug-nogc:
	$(MAKE) -C telemetrify-core debug-nogc
.PHONY: debug-nogc

debug:
	$(MAKE) -C telemetrify-core debug
.PHONY: debug

test:
		$(MAKE) -C telemetrify-core test
.PHONY: test
