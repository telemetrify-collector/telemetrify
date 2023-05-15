BUILD_ARGS=
ifeq ($(DEV),true)
	OUTPUT=out/dev
	BUILD_ARGS+=--dev
else
	OUTPUT=out/rel
endif
ARGS?=

all: build

.PHONY: all

build:
	actonc build $(BUILD_ARGS)
.PHONY: build

clean:
	rm -rf out
.PHONY: clean

run-nogc:
	GC_DONT_GC=1 $(OUTPUT)/bin/acton_streamer.test $(ARGS)

run:
	$(OUTPUT)/bin/acton_streamer.test $(ARGS)

debug-nogc:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' -ex 'set env GC_DONT_GC=1' --args $(OUTPUT)/bin/acton_streamer.test --rts-wthreads 1 $(ARGS)

debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(OUTPUT)/bin/acton_streamer.test --rts-wthreads 1 $(ARGS)
