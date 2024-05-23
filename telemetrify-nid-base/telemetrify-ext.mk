prepare-telemetrify-pkg:
	$(MAKE) -C telemetrify-ext build test
	mkdir -p packages/telemetrify/bin
	cp -p telemetrify-ext/out/bin/telemetrify_ext.server packages/telemetrify/bin/

.PHONY: prepare-telemetrify-pkg

clean-telemetrify-pkg:
	$(MAKE) -C telemetrify-ext clean
	rm -f packages/telemetrify/bin/telemetrify_ext.server
