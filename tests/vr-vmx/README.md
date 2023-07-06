# Usage

You need to build an NSO image to run this test environment.

- `git clone git@gitlab.dev.terastrm.net:abs/ned-juniper-junos-nc.git`
- `cd ned-juniper-junos`
- `make build`
- image is now available like `ned-juniper-junos-nc/testnso:6.1.2-kll`, note the NSO version at the end and your username
- makefile in this repo presumes your username, the NSO version comes from `nidvars.mk` in the repo root, which should be aligned with ned-juniper-junos repo (currently 6.1.2)
- `make start` to start environmnent, which includes big honking VMX (~7GB of RAM and 2 CPU cores at 100%)
- `make test` to test running an RPC against the vmx - currently `get-interface-information` with `interface-name=ge-0/0/0` and `detail` output

- now hack!
