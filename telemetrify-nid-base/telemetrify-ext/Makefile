build:
	acton build

.PHONY: build

test:
	acton test

.PHONY: test

clean:
	rm -rf out
	for dep in deps/*/; do \
		$(MAKE) -C $${dep} clean; \
	done;

.PHONY: clean
