BUILD_ARGS=
ifeq ($(DEV),true)
	OUTPUT=out/dev
	BUILD_ARGS+=--dev
else
	OUTPUT=out/rel
endif
ARGS?=
BIN?=acton_streamer.test

all: build

.PHONY: all

build: build-bin build-packages
.PHONY: build

build-bin:
	actonc build $(BUILD_ARGS)
.PHONY: build-bin

build-packages: build-bin
	$(MAKE) -C packages/telemetrify/src all
	rsync -E $(OUTPUT)/bin/acton_streamer.main.main packages/telemetrify/bin
.PHONY: build-packages

clean: clean-packages
	rm -rf out
.PHONY: clean

clean-packages:
	$(MAKE) -C packages/telemetrify/src clean
	-rm packages/telemetrify/bin/*
.PHONY: clean-packages

run-nogc:
	GC_DONT_GC=1 $(OUTPUT)/bin/$(BIN) $(ARGS)

run:
	$(OUTPUT)/bin/$(BIN) $(ARGS)

debug-nogc:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' -ex 'set env GC_DONT_GC=1' --args $(OUTPUT)/bin/$(BIN) --rts-wthreads 1 $(ARGS)

debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(OUTPUT)/bin/$(BIN) --rts-wthreads 1 $(ARGS)
