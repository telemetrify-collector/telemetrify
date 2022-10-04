all: build

.PHONY: all

build:
	@rm -r out/types # Workaround bug?
	actonc build

.PHONY: build
