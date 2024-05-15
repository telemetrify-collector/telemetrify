include ../testenv-common.mk
include ../testenv-common-extra.mk
CNT_PREFIX?=$(TESTENV)

SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
#DOCKER_USER:=$(shell id -u):$(shell id -g)
ifeq ($(DEV),true)
	BIN_DIR=/mnt/out/dev/bin
else
	BIN_DIR=/mnt/out/rel/bin
endif
BIN?=acton_streamer.main.server
BIN_ARGS?=
NCS_D?=ncs

export CNT_PREFIX IMAGE_BASENAME DOCKER_TAG

start:
	docker compose build
	docker compose up -d
	sleep 5
#	docker compose exec nso bash -lc "useradd -u $(shell id -u) -g $(shell id -g) -m -s /bin/bash $(USER)"
# 	make init-m3db
# 	make init-grafana
	$(MAKE) configure

# init-m3db:
# 	curl -X POST http://localhost:7201/api/v1/database/create -d '{ "type": "local", "namespaceName": "default", "retentionTime": "12h" }' | jq .
# 	sleep 20
# 	curl -X POST http://localhost:7201/api/v1/services/m3db/namespace/ready -d '{ "name": "default" }' | jq .

# init-grafana:
# 	docker compose port grafana 3000
# 	curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/orgs/1" \
# 		-m 5 -X PUT --noproxy '*' \
# 		-H 'Content-Type: application/json;charset=UTF-8' \
# 		--data-binary "{\"name\":\"NSO\"}"; echo
# 	@echo "-- Add Grafana data source for M3DB"
# 	curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/datasources" \
# 			-m 5 -X POST --noproxy '*' \
# 			-H 'Content-Type: application/json;charset=UTF-8' \
# 			--data-binary '{"id":1,"orgId":1,"name":"M3DB","type":"prometheus","typeLogoUrl":"public/app/plugins/datasource/prometheus/img/prometheus.svg","access":"proxy","url":"http://m3db:7201","password":"","user":"","database":"","basicAuth":false,"isDefault":false,"jsonData":{"esVersion":70,"logLevelField":"","logMessageField":"","maxConcurrentShardRequests":5,"timeField":"@timestamp"},"readOnly":false}'; echo
# 	@echo "-- Add Grafana dashboard for m3db"
# 	@curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/db/tsdb" \
# 			-m 5 -X DELETE --noproxy '*' \
# 			-H 'Content-Type: application/json;charset=UTF-8'; echo
# 	@SOURCE_UID=$$(curl http://admin:admin@$(shell docker compose port grafana 3000)/api/datasources/1 -m 5 --noproxy '*' | jq .uid); \
# 	 curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/db" \
# 			-m 5 -X POST --noproxy '*' \
# 			-H 'Content-Type: application/json;charset=UTF-8' \
# 			--data-binary "$$(sed "s/SOURCE_UID/$$SOURCE_UID/" dashboard-tsdb.json)"; echo
# 	#@echo "-- Add Grafana dashboard for NSO"
# 	#$(MAKE) import-dashboard
# 	@echo "-- Set m3db dashboard as default dashboard"
# 	@curl 'http://admin:admin@$(shell docker compose port grafana 3000)/api/org/preferences' \
# 			-m 5 -X PUT --noproxy '*' \
# 			-H 'X-Grafana-Org-Id: 1' \
# 			-H 'Content-Type: application/json;charset=UTF-8' \
# 			--data-binary "{\"homeDashboardId\":$$(curl -m 5 --noproxy '*' 'http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/uid/nso' 2>/dev/null | jq .dashboard.id)}"; echo

# import-dashboard:
# 	@SOURCE_UID=$$(curl http://admin:admin@$(shell docker compose port grafana 3000)/api/datasources/1 -m 5 --noproxy '*' | jq .uid); \
# 	 curl "http://admin:admin@$(shell docker compose port grafana 3000)/api/dashboards/db" \
# 			-m 5 -X POST --noproxy '*' \
# 			-H 'Content-Type: application/json;charset=UTF-8' \
# 			--data-binary "$$(sed "s/SOURCE_UID/$$SOURCE_UID/" dashboard-tsdb.json)"; echo

NSO?=-1
add-device: wait-started-nso
	$(MAKE) loadconf FILE=add-device.xml
# 	$(MAKE) wait-healthy
# 	$(MAKE) runcmdJ CMD="request devices fetch-ssh-host-keys"
# 	$(MAKE) runcmdJ CMD="request devices sync-from"

configure: add-device
	$(MAKE) loadconf FILE=add-subscription.xml
	$(MAKE) loadconf FILE=add-l3vpn-svc.xml
	docker compose cp init_l3vpn_svc_oper.py nso:/
	docker compose exec nso bash -lc "/init_l3vpn_svc_oper.py"

stop:
	docker compose down -v

test:
	$(MAKE) try-until-timeout CMD='$(MAKE) compare-oper-xml BASENAME=nw-s_networks_1.xml CLIPATH="nw-s:networks"' PERIOD=5 RETRIES=60

log:
	docker compose exec nso bash -lc "tail -n +0 -f /log/ncs-python-vm.log"

llog:
	docker compose exec nso bash -lc "less /log/ncs-python-vm.log"

debug:
	docker compose exec nso bash -lc "gdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args /nso/run/state/packages-in-use.cur/1/telemetrify/bin/telemetrify.main.server --rts-wthreads 1"

.PHONY: start stop test test-debug cli log

build-nso:
	$(MAKE) -C ../.. build tag-release

rebuild-app:
	$(MAKE) -C ../../..

rebuild-nso: build-nso
	docker compose up -d nso
	sleep 5

rebuild: rebuild-app rebuild-nso
