all: build

.PHONY: all

build:
	# Workaround https://github.com/actonlang/acton/issues/956
	actonc src/nsoapi/proto.act
	actonc build

.PHONY: build

clean:
	rm -rf out

.PHONY: clean
