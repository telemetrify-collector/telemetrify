all: fxs prepare-telemetrify-pkg
.PHONY: all

# Include standard NCS examples build definitions and rules
include $(NCS_DIR)/src/ncs/build/include.ncs.mk

SRC = $(wildcard yang/*.yang)
DIRS = ../load-dir
FXS = $(SRC:yang/%.yang=../load-dir/%.fxs)

YANGPATH += yang

NCSCPATH   = $(YANGPATH:%=--yangpath %)
YANGERPATH = $(YANGPATH:%=--path %)

fxs: $(DIRS) $(FXS)

$(DIRS):
	mkdir -p $@

../load-dir/%.fxs: yang/%.yang
	$(NCSC)  `ls $*-ann.yang  > /dev/null 2>&1 && echo "-a $*-ann.yang"` \
		--fail-on-warnings \
		$(NCSCPATH) \
		-c -o $@ $<

prepare-telemetrify-pkg:
	$(MAKE) -C acton/telemetrify-ext build test
	mkdir -p ../bin
	cp -p acton/telemetrify-ext/out/bin/telemetrify_ext.server ../bin/
.PHONY: prepare-telemetrify-pkg

clean-telemetrify-pkg:
	$(MAKE) -C acton/telemetrify-ext clean
	rm -f ../bin/telemetrify_ext.server
.PHONY: clean-telemetrify-pkg

strip:
	rm -rf acton/telemetrify-ext/out
	rm -rf acton/telemetrify-ext/deps
	rm -rf acton/telemetrify-ext/.build
	rm -f acton/telemetrify-ext/.acton.lock
.PHONY: strip

clean: clean-telemetrify-pkg
	rm -rf $(DIRS)
.PHONY: clean
