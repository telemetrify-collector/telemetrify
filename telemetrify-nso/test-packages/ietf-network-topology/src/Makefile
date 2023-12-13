all: fxs
.PHONY: all

# Include standard NCS examples build definitions and rules
include $(NCS_DIR)/src/ncs/build/include.ncs.mk

ANN_SRC = $(wildcard yang/*-ann.yang)
OSRC = $(wildcard yang/*.yang)
SRC = $(filter-out $(ANN_SRC), $(OSRC))
DIRS = ../load-dir
FXS = $(SRC:yang/%.yang=../load-dir/%.fxs)

## Uncomment and patch the line below if you have a dependency to a NED
## or to other YANG files
YANGPATH += yang

NCSCPATH   = $(YANGPATH:%=--yangpath %)
YANGERPATH = $(YANGPATH:%=--path %)

fxs: $(DIRS) $(FXS)

$(DIRS):
	mkdir -p $@

../load-dir/%.fxs: YANG_BASE=$(shell echo $*.yang | sed -e 's/\@.*//')
../load-dir/%.fxs: ANN_AUG=$(shell ls yang/$(YANG_BASE)-ann.yang  > /dev/null 2>&1 && echo "-a yang/$(YANG_BASE)-ann.yang")
../load-dir/%.fxs: yang/%.yang
	echo $(YANG_BASE)
	$(NCSC) $(ANN_AUG) \
		$(NCSCPATH) \
		-c -o $@ $<

clean:
	rm -rf $(DIRS)
.PHONY: clean
