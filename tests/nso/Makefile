SHELL=/bin/bash
SELF_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
PROJECT_DIR:=$(realpath $(SELF_DIR)/../..)

start:
	ncs --cd $(SELF_DIR)ncs
	ncs --wait-started 600

stop:
	ncs --stop

test:
	$(PROJECT_DIR)/out/rel/bin/acton-streamer
