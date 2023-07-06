# helper function to turn a string into lower case
lc = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

# Set PNS - our pseudo-namespace or pipeline namespace. All containers running
# within a CI pipeline will have the same namespace, which isn't a namespace
# like what Linux supports but it's just a prefix used for the docker containers
# to guarantee uniqueness.
ifneq ($(CI_PIPELINE_ID),)
PNS:=$(CI_PIPELINE_ID)
else
PNS:=$(shell whoami | sed 's/[^[:alnum:]._-]\+/_/g')
endif

# Determine our project name, either from CI_PROJECT_NAME which is normally set
# by GitLab CI or by looking at the name of our directory (that we are in).
ifneq ($(CI_PROJECT_NAME),)
PROJECT_NAME=$(CI_PROJECT_NAME)
else
PROJECT_NAME:=$(shell basename $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))))
endif

CNT_PREFIX?=$(call lc,$(PNS)-testenv-$(PROJECT_NAME)-$(TESTENV))

# DOCKER_ARGS contains arguments to 'docker run' for any type of container in
# the test environment.
# DOCKER_NSO_ARGS contains additional arguments specific to an NSO container.
# This includes exposing tcp/5678 for Python Remote Debugging using debugpy.
DOCKER_LABEL_ARG?=--label testenv.name=$(CNT_PREFIX)
DOCKER_ARGS+=$(DOCKER_PLATFORM_ARG)

# Determine which xargs we have. BSD xargs does not have --no-run-if-empty,
# rather, it is the default behavior so the argument is simply superfluous. We
# check if we are using GNU xargs by trying to run xargs --version and grep for
# 'GNU', if that returns 0 we are on GNU and will use 'xargs --no-run-if-empty',
# otherwise we are on BSD and will use 'xargs' straight up.
XARGS_CHECK := $(shell xargs --version 2>&1 | grep GNU >/dev/null 2>&1; echo $$?)
ifeq ($(XARGS_CHECK),0)
	XARGS := xargs --no-run-if-empty
else
	XARGS := xargs
endif
