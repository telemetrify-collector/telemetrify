try-until-timeout:
	@RETCODE=0; \
	I=0; while [ $${I} -lt $${RETRIES:-60} ]; do \
		OUTPUT="$$($(CMD) 2>&1)"; \
		RETCODE=$${?}; \
		if [ $${RETCODE} -eq 0 ]; then \
			echo -e "\033[0;32m$${OUTPUT}\033[0m"; \
			break; \
		fi; \
		if [ "$${OUTPUT}" != "$${PREV_OUTPUT}" ]; then \
			if [ -n $(ABBREV) ] && [ $$(expr $${I} + 1) -lt $${RETRIES:-60} ] && [ $$(echo "$${OUTPUT}" | wc -l) -gt $(ABBREV) ] ; then \
				echo -e "\033[0;31m$${OUTPUT}\033[0m" | head -$(ABBREV); \
				echo -e "\033[0;31m...\033[0m"; \
			else \
				echo -e "\033[0;31m$${OUTPUT}\033[0m"; \
			fi; \
			echo -e "\033[0;33mRetrying every $${PERIOD:-10} seconds. Output will be only be shown when differing from last attempt.\033[0m"; \
			PREV_OUTPUT="$${OUTPUT}"; \
		fi; \
		I=$$(expr $${I} + 1); \
		sleep $${PERIOD:-10}; \
	done; \
	exit $${RETCODE}

compare-oper-xml:
	@if [ -z "$(BASENAME)" ]; then echo "BASENAME variable must be set"; false; fi
	@if [ ! -e "expected/$(BASENAME)" ]; then echo "Missing expected/$(BASENAME)"; false; fi
	@mkdir -p output
	@$(MAKE) save-oper-xml FILE=output/$(BASENAME)
	if [ -n "$(TRANSFORM)" ] ; then \
		$(TRANSFORM) output/$(BASENAME); \
	fi
	diff expected/$(BASENAME) output/$(BASENAME)

save-oper-xml:
	@if [ -z "$(FILE)" ]; then echo "FILE variable must be set"; false; fi
	@echo "Saving oper to $(FILE)"
	docker exec -t $(CNT_PREFIX)-nso$(NSO) bash -lc "mkdir -p test/$(shell echo $(FILE) | xargs dirname)"
	@$(MAKE) runcmdJ CMD="show $(CLIPATH) | display xml | save test/$(FILE)"
	@docker cp $(CNT_PREFIX)-nso$(NSO):test/$(FILE) $(FILE)
