BUILD_ARGS=
ifeq ($(DEV),true)
	OUTPUT=out/dev
	BUILD_ARGS+=--dev
else
	OUTPUT=out/rel
endif
ARGS?=
BIN?=telemetrify.test

all: build

.PHONY: all

build:
	actonc build $(BUILD_ARGS)
.PHONY: build-bin

clean: clean-packages
	rm -rf out
.PHONY: clean

run-nogc:
	GC_DONT_GC=1 $(OUTPUT)/bin/$(BIN) $(ARGS)

run:
	$(OUTPUT)/bin/$(BIN) $(ARGS)

debug-nogc:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' -ex 'set env GC_DONT_GC=1' --args $(OUTPUT)/bin/$(BIN) --rts-wthreads 1 $(ARGS)

debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(OUTPUT)/bin/$(BIN) --rts-wthreads 1 $(ARGS)
