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
