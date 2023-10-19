CNT_PREFIX=tsdb-vmx
NSO=-1
SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)
#DOCKER_USER:=$(shell id -u):$(shell id -g)
ifeq ($(DEV),true)
	BIN_PATH=/mnt/out/dev/bin
else
	BIN_PATH=/mnt/out/rel/bin
endif
NCS_D?=ncs

start: build-nso
	docker compose build
	docker compose up -d
	sleep 5
	docker compose exec nso bash -lc "useradd -u $(shell id -u) -g $(shell id -g) -m -s /bin/bash $(USER)"
	#make init-m3db
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

runcmdC runcmdJ:
	@if [ -z "$(CMD)" ]; then echo "CMD variable must be set"; false; fi
	docker exec -t $(CNT_PREFIX)-nso$(NSO) bash -lc 'echo -e "$(CMD)" | ncs_cli --stop-on-error -$(subst runcmd,,$@)u admin'

add-vmx:
	$(MAKE) runcmdJ CMD="configure\nedit devices authgroups group vrnetlab default-map remote-name vrnetlab remote-password VR-netlab9\ncommit\nexit"
	$(MAKE) runcmdJ CMD="configure\nedit devices device vmx\nset address vmx port 830 authgroup vrnetlab\nset device-type netconf ned-id lsa-netconf\nset state admin-state unlocked\ncommit and-quit"
	$(MAKE) runcmdJ CMD="request devices device vmx ssh fetch-host-keys"
	$(MAKE) runcmdJ CMD="request devices device vmx sync-from"
	$(MAKE) runcmdJ CMD="configure\nedit devices device vmx telemetrify\nset sources netconf address 127.0.0.1 port 1234 username vrnetlab password VR-netlab9\nset subscription if source netconf-rpc-poll path /get-interface-information period 10000\n\ncommit and-quit"

add-vmanage:
	$(MAKE) runcmdJ CMD="configure\nedit devices authgroups group vrnetlab default-map remote-name vrnetlab remote-password VR-netlab9\ncommit\nexit"
	$(MAKE) runcmdJ CMD="configure\nedit devices device vmanage\nset address 127.0.0.1 port 1234 authgroup vrnetlab\nset device-type netconf ned-id netconf\nset state admin-state unlocked\ncommit and-quit"
	$(MAKE) runcmdJ CMD="configure\nedit devices device vmanage telemetrify\nset sources vmanage-http address 127.0.0.1 port 1234 username vrnetlab password VR-netlab9\nset subscription approute source vmanage-poll path /statistics/approute period 10000\n\ncommit and-quit"


stop:
	docker compose down -v

test:
	docker compose exec --user $(shell id -u):$(shell id -g) nso bash -lc "cd $(BIN_PATH) && ./acton_streamer.test tsdb-writer --rts-wthreads=1"

test-debug:
	nsenter --net=/proc/$(shell docker inspect -f '{{.State.Pid}}' "$(shell docker compose ps -q nso)")/ns/netgdb -ex 'handle SIGPWR SIGXCPU nostop noprint' --args $(BIN_PATH)/acton_streamer.test tsdb-writer

cli:
	docker compose exec nso bash -lc 'ncs_cli -u admin'

log:
	docker compose exec nso bash -lc "tail -n +0 -f /log/ncs-python-vm.log"

.PHONY: start stop test test-debug cli log

build-nso:
	$(MAKE) -C ../../streaming-nso build tag-release

rebuild-app:
	$(MAKE) -C ../..

rebuild-nso: build-nso
	docker compose up -d nso
	sleep 5

rebuild: rebuild-app rebuild-nso
