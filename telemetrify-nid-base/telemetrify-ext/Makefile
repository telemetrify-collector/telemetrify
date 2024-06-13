build:
	acton build

.PHONY: build

test:
	acton test

.PHONY: test

clean:
	rm -rf out .build build.zig build.zig.zon
	for dep in deps/*/; do \
		$(MAKE) -C $${dep} clean; \
	done;

.PHONY: clean
