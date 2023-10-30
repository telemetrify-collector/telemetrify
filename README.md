# Telemetrify

A YANG driven network telemetry collector.

One of the core design principles, if not _the_ core design principle is that
Telemetrify is YANG model driven. All data is conceptually YANG modelled. Non
YANG data and transports are supported by mapping the data into a reverse mapped
YANG model. Many good things emanate from this idea of only dealing with YANG
modeled data. It enables data validation with complex constraints and data can
be transformed by defining YANG to YANG model transforms. Without a common data
modeling language, like YANG, defining such transforms quickly becomes an
intractable problem.

The output format currently supported is to write to label centric TSDBs (Time
Series Databases). The YANG modeled data is presented as time series on a TSDB
proprietary transport. M3DB is the only supported TSDB for the time being.


## Protocol support

### Native YANG modeled transports

- NETCONF RPC polling
  - JUNOS exposes all operational state data using RPCs

### Non native YANG transports

- Cisco SD-WAN vManage HTTP polling
  - HTTPS REST API
  - reverse mapped into YANG modelled data


## Output formats

- TSDB
  - M3DB


## Deployment

Currently the only way to run Telemetrify is as a package in Cisco NSO. NSO
hosts the YANG schema used to configure Telemetrify itself as well as the YANG
schema used to validate telemetry data from network devices. The Telemetrify
configuration include things like connectivity parameters of devices and the
subscription on those devices.

In the future, Telemetrify will also support running standalone, directly
reading YANG models and exposing an interface for configuration.

### Telemetrify as an NSO package (using container w/ NSO in Docker)

1. [Install Acton](https://www.acton-lang.org/install/)
   - TLDR: `./actup` for quick install locally in project
2. Build base NSO in Docker images, using NSO version in `telemetrify-nso/nidvars.mk` (currently 6.1.4)
   - `git clone https://gitlab.com/nso-developer/nso-docker.git`
   - place NSO installer in `nso-docker/nso-installer-files`
   - `make -C nso-docker build-all tag-release-all`
3. Build `telemetrify-nso`
   - `make nso`
4. Start the `nso-tsdb` test environment
   - `cd tests/nso-tsdb`
   - `make start configure`
   - ``
5. Check out Grafana for pretty graphs
   - `make show-address`
6. TODO: describe how to configure etc

### Telemetrify as an NSO package (without containers)

1. Install NSO whichever way you like
2. Compile the package(s) in telemetrify-nso/packages
   - `telemetrify` is required
3. Load `telemetrify` package in NSO
4. ...
5. profit!
