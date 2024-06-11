include ../testenv-common.mk
CNT_PREFIX=$(TESTENV)

SHELL=/bin/bash
PROJECT_DIR:=/mnt
BUILD_PATH=$(PROJECT_DIR)/out
#DOCKER_USER:=$(shell id -u):$(shell id -g)
NCS_D?=ncs

export CNT_PREFIX

start:
	docker compose up -d
	sleep 5
	docker compose exec nso bash -lc "useradd -u $(shell id -u) -g $(shell id -g) -m -s /bin/bash $(USER)"

stop:
	docker compose down -v

test:
	echo $(MAKEFILE_LIST)
	docker compose exec nso $(BUILD_PATH)/bin/telemetrify.test $(ARGS)

log:
	docker compose exec nso bash -lc "tail -n +0 -f /log/ncs-python-vm.log"

llog:
	docker compose exec nso bash -lc "less /log/ncs-python-vm.log"

.PHONY: start stop test test-debug cli log
