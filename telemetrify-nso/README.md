# What is this?

This is a NSO system for testing Telemetify with. It uses NSO in Docker style
structure for building an NSO image that can be used for local development and
testing. It also builds a docker image that contains the `telemetrify` NSO
package which can be included in other NSO systems. There are some NEDs loaded
as test-packages for rapid iteration in local development, but that are not
included in the exported packages (test-packages are only local).
