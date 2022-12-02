all: build

.PHONY: all

build:
	# # Workaround https://github.com/actonlang/acton/issues/956
	# actonc --dev src/nsoapi/proto.act
	actonc build --dev
.PHONY: build

clean:
	rm -rf out
.PHONY: clean

run-nogc:
	GC_DONT_GC=1 out/dev/bin/nsoapi.maapi

run:
	out/dev/bin/nsoapi.maapi

debug-nogc:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' -ex 'set env GC_DONT_GC=1' --args out/dev/bin/nsoapi.maapi --rts-wthreads 1

debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args out/dev/bin/nsoapi.maapi --rts-wthreads 1
