# You can set the default NSO_IMAGE_PATH & PKG_PATH to point to your docker
# registry so that developers don't have to manually set these variables.
# Similarly for NSO_VERSION you can set a default version. Note how the ?=
# operator only sets these variables if not already set, thus you can easily
# override them by explicitly setting them in your environment and they will be
# overridden by variables in CI.
export NSO_IMAGE_PATH ?= gitlab.dev.terastrm.net:4567/abs/nso-docker/
export PKG_PATH ?= gitlab.dev.terastrm.net:4567/abs/
export NSO_VERSION ?= 6.1.4
