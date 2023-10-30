# empty means latest
PREFERRED_ACTON_VERSION=

# Initial check for actonc in the PATH
ACTONC := $(shell which actonc)

# If not found in PATH, check the local directory
ifeq ($(ACTONC),)
  #LOCAL_ACTON_DIR := $(shell pwd)/acton-$(PREFERRED_ACTON_VERSION)
  LOCAL_ACTON_DIR := $(shell pwd)/acton
  ACTONC := $(shell test -e $(LOCAL_ACTON_DIR)/bin/actonc && echo $(LOCAL_ACTON_DIR)/bin/actonc)
endif

# If still not found, raise an error
ifeq ($(ACTONC),)
  $(error Acton compiler not found. Please run ./actup to install Acton locally in this project or see https://www.acton-lang.org/install/ for more options)
endif

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
	$(ACTONC) build $(BUILD_ARGS)
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
