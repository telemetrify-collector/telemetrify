SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
DOCKER_USER:=$(shell id -u):$(shell id -g)
BUILD_PATH=$(PROJECT_DIR)/out
NCS_D?=ncs

start:
	DOCKER_USER=$(DOCKER_USER) docker compose up -d
	sleep 5
	make init-m3db
	make init-grafana

init-m3db:
	curl -X POST http://localhost:7201/api/v1/database/create -d '{ "type": "local", "namespaceName": "default", "retentionTime": "12h" }' | jq .
	sleep 15
	curl -X POST http://localhost:7201/api/v1/services/m3db/namespace/ready -d '{ "name": "default" }' | jq .

init-grafana:
	docker compose port grafana 3000
	curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/orgs/1" \
		-m 5 -X PUT --noproxy '*' \
		-H 'Content-Type: application/json;charset=UTF-8' \
		--data-binary "{\"name\":\"NSO\"}"; echo
	@echo "-- Add Grafana data source for M3DB"
	curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/datasources" \
			-m 5 -X POST --noproxy '*' \
			-H 'Content-Type: application/json;charset=UTF-8' \
			--data-binary '{"id":1,"orgId":1,"name":"M3DB","type":"prometheus","typeLogoUrl":"public/app/plugins/datasource/prometheus/img/prometheus.svg","access":"proxy","url":"http://m3db:7201","password":"","user":"","database":"","basicAuth":false,"isDefault":false,"jsonData":{"esVersion":70,"logLevelField":"","logMessageField":"","maxConcurrentShardRequests":5,"timeField":"@timestamp"},"readOnly":false}'; echo
	@echo "-- Add Grafana dashboard for m3db"
	@curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/db/tsdb" \
			-m 5 -X DELETE --noproxy '*' \
			-H 'Content-Type: application/json;charset=UTF-8'; echo
	@SOURCE_UID=$$(curl http://admin:admin@$(shell docker compose port grafana 3000)/api/datasources/1 -m 5 --noproxy '*' | jq .uid); \
	 curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/db" \
			-m 5 -X POST --noproxy '*' \
			-H 'Content-Type: application/json;charset=UTF-8' \
			--data-binary "$$(sed "s/SOURCE_UID/$$SOURCE_UID/" dashboard-tsdb.json)"; echo
	#@echo "-- Add Grafana dashboard for NSO"
	#$(MAKE) import-dashboard
	@echo "-- Set m3db dashboard as default dashboard"
	@curl 'http://admin:admin@$(shell docker compose port grafana 3000)/api/org/preferences' \
			-m 5 -X PUT --noproxy '*' \
			-H 'X-Grafana-Org-Id: 1' \
			-H 'Content-Type: application/json;charset=UTF-8' \
			--data-binary "{\"homeDashboardId\":$$(curl -m 5 --noproxy '*' 'http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/uid/nso' 2>/dev/null | jq .dashboard.id)}"; echo

import-dashboard:
	@SOURCE_UID=$$(curl http://admin:admin@$(shell docker compose port grafana 3000)/api/datasources/1 -m 5 --noproxy '*' | jq .uid); \
	 curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/db" \
			-m 5 -X POST --noproxy '*' \
			-H 'Content-Type: application/json;charset=UTF-8' \
			--data-binary "$$(sed "s/SOURCE_UID/$$SOURCE_UID/" dashboard-tsdb.json)"; echo

stop:
	docker compose down

test:
	$(BUILD_PATH)/bin/tsdb.test

test-debug:
	gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BUILD_PATH)/bin/prometheusapi.test --rts-wthreads 1 $(ARGS)

.PHONY: start stop test test-debug cli
